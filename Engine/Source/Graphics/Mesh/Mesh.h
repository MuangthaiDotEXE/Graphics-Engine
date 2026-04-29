#pragma once

#ifndef MESH_H
#define MESH_H

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/VAO.h"
#include "Graphics/Shader/VBO.h"
#include "Graphics/Shader/EBO.h"
#include "Graphics/Texture/Texture.h"

namespace Engine
{
	class Mesh
	{
	public:
		Core::Shader shader;
		Core::VAO vao;
		Core::VBO vbo;
		Core::EBO ebo;
		Core::Texture diffuse;
		Core::Texture specular;

		std::string name = "Mesh";

	public:
		struct MeshTransform
		{
			glm::vec3 position = glm::vec3(0.0f);
			glm::vec3 rotation = glm::vec3(0.0f);
			glm::vec3 scale = glm::vec3(1.0f);

			glm::mat4 GetMatrix() const;
		};

		MeshTransform transform;

	public:		
		Mesh(const std::string& vertexShader, const std::string& fragmentShader, std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const Core::Texture& diffuse, const Core::Texture& specular);
		Mesh(const Core::Shader& shader, std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const Core::Texture& diffuse, const Core::Texture& specular);
		virtual ~Mesh() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;
	};
}

#endif
