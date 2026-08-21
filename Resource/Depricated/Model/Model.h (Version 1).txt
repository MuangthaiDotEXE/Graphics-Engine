#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <stdexcept>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <JSON/json.hpp>

#include "../Shader/Shader.h"
#include "../Shader/VBO.h"
#include "../Texture/Texture.h"
#include "../../Utility/Utility.h"

using json = nlohmann::json;

namespace Core
{
	class Model
	{
	private:
		std::string file;
		std::vector<unsigned char> data;
		json JSON;

		std::vector<glm::vec3> translationsMeshes;
		std::vector<glm::quat> rotationsMeshes;
		std::vector<glm::vec3> scalesMeshes;
		std::vector<glm::mat4> matricesMeshes;

		std::vector<std::string> loadedTextureName;
		std::vector<Texture> loadedTexture;

	public:
		Model(const Shader& shader, std::string file);
		virtual ~Model() = default;

		void Update();

	private:
		void LoadMesh(unsigned int indexMesh);
		void TraverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

		std::vector<unsigned char> GetData();
		std::vector<float> GetFloats(json accessor);
		std::vector<GLuint> GetIndices(json accessor);
		std::vector<Core::Texture> GetTextures();

		std::vector<Vertex> AssembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureUVs);

		std::vector<glm::vec2> GroupFloatVector2(std::vector<float> floatVector);
		std::vector<glm::vec3> GroupFloatVector3(std::vector<float> floatVector);
		std::vector<glm::vec4> GroupFloatVector4(std::vector<float> floatVector);
	};
}

#endif
