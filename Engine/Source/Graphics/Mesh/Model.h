#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <concepts>
#include <string>
#include <vector>
#include <stdexcept>

#include <glm/glm.hpp>
#include "JSON/json.hpp"

#include "Mesh.h"

using JSON = nlohmann::json;

namespace Engine
{
	class Model
	{
	private:
		JSON json;

		std::string file;
		std::vector<unsigned char> data;

	public:
		Model(const std::string& file);

		void Render();
		void Update();

	private:
		std::vector<unsigned char> GetData();
		std::vector<float> GetFloats(JSON accessor);
		std::vector<GLuint> GetIndices(JSON accessor);

		std::vector<glm::vec2> GroupFloatsVector2(std::vector<float> floatVector);
		std::vector<glm::vec3> GroupFloatsVector3(std::vector<float> floatVector);
		std::vector<glm::vec4> GroupFloatsVector4(std::vector<float> floatVector);

		std::vector<vertex> assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureUVs);

		template<string T>
		std::string ReadFile(const T& path);
	};
}

#endif
