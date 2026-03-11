#include "Model.h"

Core::Model::Model(const std::string& file)
    : file(file), texture()
{
	std::string text = ReadFile(file);
    json = JSON::parse(text);
    data = GetData();
}

void Core::Model::Render()
{
}

void Core::Model::Update()
{
}

void Core::Model::loadMesh(unsigned int indicesMesh)
{
    unsigned int positionAccessorsIndices = json["meshes"][indicesMesh]["primitives"][0]["attributes"]["POSITION"];
    unsigned int normalAccessorsIndices = json["meshes"][indicesMesh]["primitives"][0]["attributes"]["NORMAL"];
    unsigned int textureAccessorsIndices = json["meshes"][indicesMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
    unsigned int indicesAccessorsIndices = json["meshes"][indicesMesh]["primitives"][0]["indices"];

    std::vector<float> positionVector = GetFloats(json["accessors"][positionAccessorsIndices]);
    std::vector<glm::vec3> positions = GroupFloatsVector3(positionVector);
    std::vector<float> normalVector = GetFloats(json["accessors"][normalAccessorsIndices]);
    std::vector<glm::vec3> normals = GroupFloatsVector3(normalVector);
    std::vector<float> textureVector = GetFloats(json["accessors"][textureAccessorsIndices]);
    std::vector<glm::vec2> textureUVs = GroupFloatsVector2(textureVector);

    std::vector<vertex> vertices = AssembleVertices(positions, normals, textureUVs);
    std::vector<GLuint> indices = GetIndices(json["accessors"][indicesAccessorsIndices]);
    std::vector<Texture> textures = GetTextures();
}

std::vector<unsigned char> Core::Model::GetData()
{
    std::string byteText;
    std::string uri = json["buffers"][0]["uri"];

    std::string file = std::string(this->file);
    std::string directory = file.substr(0, file.find_last_of("/") + 1);
    byteText = ReadFile(directory + uri);

    std::vector<unsigned char> data(byteText.begin(), byteText.end());
    return data;
}

std::vector<float> Core::Model::GetFloats(JSON accessor)
{
    std::vector<float> floatVector;

    unsigned int bufferViewIndex = accessor.value("bufferView", 1);
    unsigned int count = accessor["count"];
    unsigned int accessorByteOffset = accessor.value("byteOffset", 0);
    std::string type = accessor["type"];

    JSON bufferView = json["bufferViews"][bufferViewIndex];
    unsigned int byteOffset = bufferView.value("byteOffset", 0);

    unsigned int numberPerVertex;
    if (type == "SCALAR") numberPerVertex = 1;
    else if (type == "VEC2") numberPerVertex = 2;
    else if (type == "VEC3") numberPerVertex = 3;
    else if (type == "VEC4") numberPerVertex = 4;
    else throw std::invalid_argument("Invalid type given. Valid types are: 'SCALAR', 'VEC2', 'VEC3', or 'VEC4' (JSON)\n)");

    unsigned int beginningData = byteOffset + accessorByteOffset;
    unsigned int dataLength = count * 4 * numberPerVertex;
    for (unsigned int i = beginningData; i < beginningData + +dataLength; i += 4)
    {
        unsigned char bytes[] = { data[i], data[i + 1], data[i + 2], data[i + 3] };

        float value;
        std::memcpy(&value, bytes, sizeof(float));
        floatVector.emplace_back(value);
    }

    return floatVector;
}

std::vector<GLuint> Core::Model::GetIndices(JSON accessor)
{
    std::vector<GLuint> indices;

    unsigned int bufferViewIndex = accessor.value("bufferView", 1);
    unsigned int count = accessor["count"];
    unsigned int accessorByteOffset = accessor.value("byteOffset", 0);
    unsigned int componentType = accessor["componentType"];

    JSON bufferView = json["bufferViews"][bufferViewIndex];
    unsigned int byteOffset = bufferView.value("byteOffset", 0);

    unsigned int beginningData = byteOffset + accessorByteOffset;
    if (componentType == 5125)
    {
        for (unsigned int i = beginningData; i < byteOffset + accessorByteOffset + count * 4; i+= 4)
        {
            unsigned char bytes[] = { data[i], data[i + 1], data[i + 2], data[i + 3] };

            unsigned int value;
            std::memcpy(&value, bytes, sizeof(unsigned int));
            indices.emplace_back((GLuint)value);
        }
    }
    else if (componentType == 5123)
    {
        for (unsigned int i = beginningData; i < byteOffset + accessorByteOffset + count * 2; i += 2)
        {
            unsigned char bytes[] = { data[i], data[i + 1] };

            unsigned short value;
            std::memcpy(&value, bytes, sizeof(unsigned short));
            indices.emplace_back((GLuint)value);
        }
    }
    else if (componentType == 5122)
    {
        for (unsigned int i = beginningData; i < byteOffset + accessorByteOffset + count * 2; i += 2)
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
    std::string directory = fileString.substr(0, fileString.find_last_of("/") + 1);

    for (unsigned int i = 0; i < json["images"].size(); i++)
    {
        std::string texturePath = json["images"][i]["uri"];

        bool skip = false;
        for (unsigned int j = 0; j < loadedTextureName.size(); j++)
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
                Texture diffuse = Texture(directory + texturePath, "diffuse", loadedTexture.size());
                textures.emplace_back(diffuse);
                loadedTexture.emplace_back(diffuse);
                loadedTextureName.emplace_back(texturePath);
            }
            else if (texturePath.find("metallicRoughness") != std::string::npos)
            {
                Texture specular = Texture(directory + texturePath, "specular", loadedTexture.size());
                textures.emplace_back(specular);
                loadedTexture.emplace_back(specular);
                loadedTextureName.emplace_back(texturePath);
            }
        }
    }
    
    return textures;
}

std::vector<glm::vec2> Core::Model::GroupFloatsVector2(std::vector<float> floatVector)
{
    std::vector<glm::vec2> vector;

    for (unsigned int i = 0; i < floatVector.size(); i += 2)
    {
        vector.emplace_back(glm::vec2(0, 0));

        for (unsigned int j = 0; j < 2; j++)
        {
            vector.back()[j] = floatVector[i + j];
        }
    }

    return vector;
}

std::vector<glm::vec3> Core::Model::GroupFloatsVector3(std::vector<float> floatVector)
{
    std::vector<glm::vec3> vector;

    for (unsigned int i = 0; i < floatVector.size(); i += 3)
    {
        vector.emplace_back(glm::vec3(0, 0, 0));

        for (unsigned int j = 0; j < 3; j++)
        {
            vector.back()[j] = floatVector[i + j];
        }
    }

    return vector;
}

std::vector<glm::vec4> Core::Model::GroupFloatsVector4(std::vector<float> floatVector)
{
    std::vector<glm::vec4> vector;

    for (unsigned int i = 0; i < floatVector.size(); i += 4)
    {
        vector.emplace_back(glm::vec4(0, 0, 0, 0));

        for (unsigned int j = 0; j < 4; j++)
        {
            vector.back()[j] = floatVector[i + j];
        }
    }

    return vector;
}

std::vector<vertex> Core::Model::AssembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureUVs)
{
    std::vector<vertex> vertices;

    for (unsigned int i = 0; i < positions.size(); i++)
    {
        vertices.emplace_back
        (
            vertex
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
