#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <concepts>
#include <vector>
#include <stdexcept>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <JSON/json.hpp>

#include "Graphics/Shader/VBO.h"
#include "Graphics/Texture/Texture.h"
#include "Utility/Utility.h"
//#include "Mesh.h"

using JSON = nlohmann::json;

namespace Core
{
	class Model
	{
	private:
		Texture texture;

		JSON json;

		std::string file;
		std::vector<unsigned char> data;

		std::vector<std::string> loadedTextureName;
		std::vector<Texture> loadedTexture;

	public:
		Model(const std::string& file);

		void Render();
		void Update();

	private:
		void loadMesh(unsigned int indicesMesh);

		std::vector<unsigned char> GetData();
		std::vector<float> GetFloats(JSON accessor);
		std::vector<GLuint> GetIndices(JSON accessor);
		std::vector<Core::Texture> GetTextures();

		std::vector<glm::vec2> GroupFloatsVector2(std::vector<float> floatVector);
		std::vector<glm::vec3> GroupFloatsVector3(std::vector<float> floatVector);
		std::vector<glm::vec4> GroupFloatsVector4(std::vector<float> floatVector);

		std::vector<vertex> AssembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureUVs);
	};
}

#endif
