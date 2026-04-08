#include "Model.h"

Core::Model::Model(const Shader& shader, std::string file)
{
	std::string text = ReadFile(file);
	JSON = json::parse(text);

	this->file = file;
	data = GetData();

	TraverseNode(0);
}

void Core::Model::LoadMesh(unsigned int indexMesh)
{
	unsigned int positionAccessorIndices = JSON["meshes"][indexMesh]["primitives"][0]["attributes"]["POSITION"];
	unsigned int normalAccessorIndices = JSON["meshes"][indexMesh]["primitives"][0]["attributes"]["NORMAL"];
	unsigned int textureAccessorIndices = JSON["meshes"][indexMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
	unsigned int indicesAccessorIndices = JSON["meshes"][indexMesh]["primitives"][0]["indices"];

	std::vector<float> positionVector = GetFloats(JSON["accessors"][positionAccessorIndices]);
	std::vector<glm::vec3> positions = GroupFloatVector3(positionVector);
	std::vector<float> normalVector = GetFloats(JSON["accessors"][normalAccessorIndices]);
	std::vector<glm::vec3> normals = GroupFloatVector3(normalVector);
	std::vector<float> textureVector = GetFloats(JSON["accessors"][textureAccessorIndices]);
	std::vector<glm::vec2> textureUVs = GroupFloatVector2(textureVector);

	std::vector<Vertex> vertices = AssembleVertices(positions, normals, textureUVs);
	std::vector<GLuint> indices = GetIndices(JSON["accessors"][indicesAccessorIndices]);
	std::vector<Texture> textures = GetTextures();

	//meshes.emplace_back(Mesh(vertices, indices, textures));
}

void Core::Model::TraverseNode(unsigned int nextNode, glm::mat4 matrix)
{
	json node = JSON["nodes"][nextNode];

	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	if (node.find("translation") != node.end())
	{
		float translationValues[3];
		for (unsigned int i = 0; i < node["translation"].size(); i++)
		{
			translationValues[i] = (node["translation"][i]);
		}

		translation = glm::make_vec3(translationValues);
	}

	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	if (node.find("rotation") != node.end())
	{
		float rotationValues[4] =
		{
			node["rotation"][3],
			node["rotation"][0],
			node["rotation"][1],
			node["rotation"][2]
		};

		rotation = glm::make_quat(rotationValues);
	}

	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	if (node.find("scale") != node.end())
	{
		float scaleValues[3];
		for (unsigned int i = 0; i < node["scale"].size(); i++)
		{
			scaleValues[i] = (node["scale"][i]);
		}

		scale = glm::make_vec3(scaleValues);
	}

	glm::mat4 matrixNode = glm::mat4(1.0f);
	if (node.find("matrix") != node.end())
	{
		float matrixValues[16];
		for (unsigned int i = 0; i < node["matrix"].size(); i++)
		{
			matrixValues[i] = (node["matrix"][i]);
		}

		matrixNode = glm::make_mat4(matrixValues);
	}

	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	glm::mat4 matrixNextNode = matrix * matrixNode * trans * rot * sca;

	if (node.find("mesh") != node.end())
	{
		translationsMeshes.emplace_back(translation);
		rotationsMeshes.emplace_back(rotation);
		scalesMeshes.emplace_back(scale);
		matricesMeshes.emplace_back(matrixNextNode);

		LoadMesh(node["mesh"]);
	}

	if (node.find("children") != node.end())
	{
		for (unsigned int i = 0; i < node["children"].size(); i++)
		{
			TraverseNode(node["children"][i], matrixNextNode);
		}
	}
}

std::vector<unsigned char> Core::Model::GetData()
{
	std::string bytesText;
	std::string uri = JSON["buffers"][0]["uri"];

	std::string fileString = std::string(file);
	std::string fileDirectory = fileString.substr(0, fileString.find_last_of("/") + 1);
	bytesText = ReadFile((fileDirectory + uri));

	std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
	return data;
}

std::vector<float> Core::Model::GetFloats(json accessor)
{
	std::vector<float> floatVector;

	unsigned int bufferViewIndex = accessor.value("bufferView", 1);
	unsigned int count = accessor["count"];
	unsigned int accessorByteOffset = accessor.value("byteOffset", 0);
	std::string type = accessor["type"];

	json bufferView = JSON["bufferViews"][bufferViewIndex];
	unsigned int byteOffset = bufferView.value("byteOffset", 0);

	unsigned int numberPerVertex;
	if (type == "SCALAR") numberPerVertex = 1;
	else if (type == "VEC2") numberPerVertex = 2;
	else if (type == "VEC3") numberPerVertex = 3;
	else if (type == "VEC4") numberPerVertex = 4;
	else throw std::invalid_argument("Type is invalid. Support types are 'SCALAR', 'VEC2', 'VEC3' and 'VEC4' (Nlohmann JSON)");

	unsigned int dataBeginning = byteOffset + accessorByteOffset;
	unsigned int dataLength = count * 4 * numberPerVertex;
	for (unsigned int i = dataBeginning; i < dataBeginning + dataLength; i += 4)
	{
		unsigned char bytes[] = { data[i], data[i + 1], data[i + 2], data[i + 3] };
		float value;
		std::memcpy(&value, bytes, sizeof(float));

		floatVector.emplace_back(value);
	}

	return floatVector;
}

std::vector<GLuint> Core::Model::GetIndices(json accessor)
{
	std::vector<GLuint> indices;

	unsigned int bufferViewIndex = accessor.value("bufferView", 0);
	unsigned int count = accessor["count"];
	unsigned int accessorByteOffset = accessor.value("byteOffset", 0);
	unsigned int componentType = accessor["componentType"];

	json bufferView = JSON["bufferViews"][bufferViewIndex];
	unsigned int byteOffset = bufferView.value("byteOffset", 0);

	unsigned int dataBeginning = byteOffset + accessorByteOffset;

	if (componentType == 5125)
	{
		for (unsigned int i = dataBeginning; i < byteOffset + accessorByteOffset + count * 4; i += 4)
		{
			unsigned char bytes[] = { data[i], data[i + 1], data[i + 2], data[i + 3] };
			unsigned int value;
			std::memcpy(&value, bytes, sizeof(unsigned int));

			indices.emplace_back((GLuint)value);
		}
	}
	else if (componentType == 5123)
	{
		for (unsigned int i = dataBeginning; i < byteOffset + accessorByteOffset + count * 2; i += 2)
		{
			unsigned char bytes[] = { data[i], data[i + 1] };
			unsigned short value;
			std::memcpy(&value, bytes, sizeof(unsigned short));

			indices.emplace_back((GLuint)value);
		}
	}
	else if (componentType == 5122)
	{
		for (unsigned int i = dataBeginning; i < byteOffset + accessorByteOffset + count * 2; i += 2)
		{
			unsigned char bytes[] = { data[i], data[i + 1] };
			short value;
			std::memcpy(&value, bytes, sizeof(short));

			indices.emplace_back((GLuint)value);
		}
	}

	return indices;
}

std::vector<Core::Texture> Core::Model::GetTextures()
{
	std::vector<Texture> textures;

	std::string fileString = std::string(file);
	std::string fileDirectory = file.substr(0, fileString.find_last_of("/") + 1);

	for (unsigned int i = 0; i < JSON["images"].size(); i++)
	{
		std::string texturePath = JSON["images"][i]["uri"];

		bool skip = false;
		for (unsigned int j = 0; i < loadedTextureName.size(); j++)
		{
			if (loadedTextureName[j] == texturePath)
			{
				textures.emplace_back(loadedTexture[j]);
				skip = true;

				break;
			}
		}

		if (!skip)
		{
			if (texturePath.find("baseColor") != std::string::npos)
			{
				Texture diffuse = Texture((fileDirectory + texturePath), "diffuse", loadedTexture.size());
				textures.emplace_back(diffuse);
				loadedTexture.emplace_back(diffuse);
				loadedTextureName.emplace_back(texturePath);
			}
			else if (texturePath.find("metallicRoughness") != std::string::npos)
			{
				Texture specular = Texture((fileDirectory + texturePath), "specular", loadedTexture.size());
				textures.emplace_back(specular);
				loadedTexture.emplace_back(specular);
				loadedTextureName.emplace_back(texturePath);
			}
		}
	}

	return textures;
}

std::vector<Vertex> Core::Model::AssembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureUVs)
{
	std::vector<Vertex> vertices;
	for (int i = 0; i < positions.size(); i++)
	{
		vertices.emplace_back
		(
			Vertex
			{
				positions[i],
				glm::vec3(1.0f, 1.0f, 1.0f),
				textureUVs[i],
				normals[i]
			}
		);
	}

	return vertices;
}

std::vector<glm::vec2> Core::Model::GroupFloatVector2(std::vector<float> floatVector)
{
	const unsigned int floatsPerVector = 2;

	std::vector<glm::vec2> vectors;
	for (unsigned int i = 0; i < floatVector.size(); i += floatsPerVector)
	{
		vectors.emplace_back(glm::vec2(0, 0));

		for (unsigned int j = 0; j < floatsPerVector; j++)
		{
			vectors.back()[j] = floatVector[i + j];
		}
	}

	return vectors;
}

std::vector<glm::vec3> Core::Model::GroupFloatVector3(std::vector<float> floatVector)
{
	const unsigned int floatsPerVector = 3;

	std::vector<glm::vec3> vectors;
	for (unsigned int i = 0; i < floatVector.size(); i += floatsPerVector)
	{
		vectors.emplace_back(glm::vec3(0, 0, 0));

		for (unsigned int j = 0; j < floatsPerVector; j++)
		{
			vectors.back()[j] = floatVector[i + j];
		}
	}

	return vectors;
}

std::vector<glm::vec4> Core::Model::GroupFloatVector4(std::vector<float> floatVector)
{
	const unsigned int floatsPerVector = 4;

	std::vector<glm::vec4> vectors;
	for (unsigned int i = 0; i < floatVector.size(); i += floatsPerVector)
	{
		vectors.emplace_back(glm::vec4(0, 0, 0, 0));

		for (unsigned int j = 0; j < floatsPerVector; j++)
		{
			vectors.back()[j] = floatVector[i + j];
		}
	}

	return vectors;
}
