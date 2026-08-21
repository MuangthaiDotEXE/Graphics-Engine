#include "Model.h"

namespace
{
	glm::mat4 ConvertMatrix(const aiMatrix4x4& matrix)
	{
		return glm::mat4(
			matrix.a1, matrix.b1, matrix.c1, matrix.d1,
			matrix.a2, matrix.b2, matrix.c2, matrix.d2,
			matrix.a3, matrix.b3, matrix.c3, matrix.d3,
			matrix.a4, matrix.b4, matrix.c4, matrix.d4
		);
	}
}

Engine::Model::SubMesh::SubMesh(std::vector<Vertex>& vertices,
	std::vector<GLuint>& indices,
	std::optional<std::vector<std::string>> diffusePaths,
	std::optional<std::vector<std::string>> specularPaths,
	Core::Shader& shader
)
	: hasDiffuse(diffusePaths.has_value()),
	hasSpecular(specularPaths.has_value()),
	vao(),
	vbo(vertices),
	ebo(indices),
	diffuse(std::move(diffusePaths), "diffuse", 0),
	specular(std::move(specularPaths), "specular", 1),
	indexCount(static_cast<GLsizei>(indices.size()))
{
	vao.Bind();
	vbo.Bind();
	ebo.Bind();

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
	vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));
	vao.LinkAttributes(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, textureUV));
	vao.LinkAttributes(vbo, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	if (hasDiffuse)
	{
		diffuse.SetUnit(shader, "diffuseSampler", 0);
	}
	if (hasSpecular)
	{
		specular.SetUnit(shader, "specularSampler", 1);
	}
}

Engine::Model::Model(const std::string& path, bool flipUVs)
	: Mesh(ProjectDirectory "/Resource/Shader/Mesh/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh/Mesh.frag", DummyVertices(), DummyIndices(), std::nullopt, std::nullopt),
	flipUVs(flipUVs)
{
	LoadModel(path);
}

Engine::Model::Model(const std::string& path, const Core::Shader& shader, bool flipUVs)
	: Mesh(shader, DummyVertices(), DummyIndices(), std::nullopt, std::nullopt),
	flipUVs(flipUVs)
{
	LoadModel(path);
}

void Engine::Model::Render()
{
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Model::Update()
{
	shader.Activate();

	for (auto& subMesh : subMeshes)
	{
		subMesh->vao.Bind();

		glUniform1i(glGetUniformLocation(shader.programID, "hasDiffuse"), subMesh->hasDiffuse ? GL_TRUE : GL_FALSE);
		glUniform1i(glGetUniformLocation(shader.programID, "hasSpecular"), subMesh->hasSpecular ? GL_TRUE : GL_FALSE);

		if (subMesh->hasDiffuse)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, subMesh->diffuse.GetID(0));
		}
		if (subMesh->hasSpecular)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, subMesh->specular.GetID(0));
		}

		glDrawElements(GL_TRIANGLES, subMesh->indexCount, GL_UNSIGNED_INT, (void*)0);

		subMesh->vao.Unbind();
	}
}

size_t Engine::Model::GetSubMeshCount() const
{
	return subMeshes.size();
}

void Engine::Model::LoadModel(const std::string& path)
{
	Assimp::Importer importer;

	unsigned int flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace;
	if (flipUVs)
	{
		flags |= aiProcess_FlipUVs;
	}

	const aiScene* scene = importer.ReadFile(path, flags);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		throw std::runtime_error(std::format(R"(Failed to load model with path: {} 
With error: {} (Assimp model import library))",
path,
importer.GetErrorString()));
	}

	std::filesystem::path modelPath(path);
	directory = modelPath.parent_path().string();

	//size_t slash = path.find_last_of("/\\");
	//directory = (slash != std::string::npos) ? path.substr(0, slash) : ".";

	subMeshes.reserve(scene->mNumMeshes);
	ProcessNode(scene->mRootNode, scene, glm::mat4(1.0f));

#ifndef NDEBUG
	if (subMeshes.empty())
	{
		std::println(stdout, "\033[33m[Warn] Model loaded from path: '{}' contains no usable meshes (Assimp model import library)\033[0m\n", path);
	}
#endif
}

void Engine::Model::ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& parentTransform)
{
	glm::mat4 nodeTransform = parentTransform * ConvertMatrix(node->mTransformation);

	for (size_t i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene, nodeTransform);
	}

	for (size_t i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene, nodeTransform);
	}
}

void Engine::Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& nodeTransform)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	vertices.reserve(mesh->mNumVertices);

	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(nodeTransform)));

	glm::vec3 materialColor = glm::vec3(1.0f);
	if (scene->HasMaterials())
	{
		aiColor3D diffuseColor(1.0f, 1.0f, 1.0f);
		if (scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS)
		{
			materialColor = glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);
		}
	}

	bool hasVertexColors = mesh->HasVertexColors(0);

	for (size_t i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex{};

		glm::vec4 position = nodeTransform * glm::vec4(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z, 1.0f);
		vertex.position = glm::vec3(position);

		if (hasVertexColors)
		{
			vertex.color = glm::vec3(mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b);
		}
		else
		{
			vertex.color = materialColor;
		}

		if (mesh->HasNormals())
		{
			glm::vec3 normal = normalMatrix * glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			vertex.normal = glm::normalize(normal);
		}
		else
		{
			vertex.normal = glm::vec3(0.0f);
		}

		if (mesh->HasTextureCoords(0))
		{
			vertex.textureUV = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
		{
			vertex.textureUV = glm::vec2(0.0f);
		}

		vertices.emplace_back(vertex);
	}

	indices.reserve(static_cast<size_t>(mesh->mNumFaces) * 3);

	for (size_t i = 0; i < mesh->mNumFaces; ++i)
	{
		const aiFace& face = mesh->mFaces[i];

		for (size_t j = 0; j < face.mNumIndices; ++j)
		{
			indices.emplace_back(face.mIndices[j]);
		}
	}

	std::optional<std::vector<std::string>> diffusePaths = std::nullopt;
	std::optional<std::vector<std::string>> specularPaths = std::nullopt;

	if (scene->HasMaterials())
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		diffusePaths = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
		specularPaths = LoadMaterialTextures(material, aiTextureType_SPECULAR);
	}

	subMeshes.emplace_back(std::make_unique<SubMesh>(vertices, indices, diffusePaths, specularPaths, shader));
}

std::optional<std::vector<std::string>> Engine::Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type)
{
	std::vector<std::string> paths;

	unsigned int count = material->GetTextureCount(type);
	if (count == 0 && type == aiTextureType_DIFFUSE)
	{
		type = aiTextureType_BASE_COLOR;
		count = material->GetTextureCount(type);
	}
	if (count == 0 && type == aiTextureType_SPECULAR)
	{
		type = aiTextureType_UNKNOWN;
		count = material->GetTextureCount(type);
	}

	paths.reserve(count);

	for (size_t i = 0; i < count; ++i)
	{
		aiString str;
		if (material->GetTexture(type, i, &str) != AI_SUCCESS)
		{
			continue;
		}

		std::string texturePath = str.C_Str();
		if (texturePath.empty() || texturePath[0] == '*')
		{
#ifndef NDEBUG
			//std::println(stdout, "\033[33m[Warn] Skipping embedded texture \'{}\'. Embedded textures are not supported, please export/extract the texture (Assimp model import library)\033[0m\n", texturePath);
#endif
			continue;
		}

		std::filesystem::path textureFilePath(texturePath);
		std::filesystem::path resolvedPath;

		if (textureFilePath.is_absolute())
		{
			if (std::filesystem::exists(textureFilePath))
			{
				resolvedPath = textureFilePath;
			}
			else
			{
				resolvedPath = std::filesystem::path(directory) / textureFilePath.filename();
			}
		}
		else
		{
			resolvedPath = std::filesystem::path(directory) / textureFilePath;
		}

		if (std::filesystem::exists(resolvedPath))
		{
			paths.emplace_back(resolvedPath.generic_string());
		}
#ifndef NDEBUG
		else
		{
			std::println(stdout, "\033[33m[Warn] Texture referenced in material does not exist: '{}'. Falling back to untextured rendering.\033[0m\n", resolvedPath.string());
		}
#endif

		//paths.emplace_back(directory + "/" + texturePath);
	}

	if (paths.empty())
	{
		return std::nullopt;
	}

	return paths;
}

std::vector<Vertex>& Engine::Model::DummyVertices()
{
	static std::vector<Vertex> vertices
	{
		Vertex{ glm::vec3(0.0f), glm::vec3(1.0f), glm::vec2(0.0f), glm::vec3(0.0f, 1.0f, 0.0f) }
	};

	return vertices;
}

std::vector<GLuint>& Engine::Model::DummyIndices()
{
	static std::vector<GLuint> indices{ 0 };

	return indices;
}
