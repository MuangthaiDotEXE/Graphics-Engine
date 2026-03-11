#pragma once

#ifndef MESH_H
#define MESH_H

#include <string>

#include <glad/gl.h>

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
		
		Mesh(const std::string& vertexShader, const std::string& fragmentShader, std::vector<vertex>& vertices, std::vector<GLuint>& indices, const Core::Texture& diffuse, const Core::Texture& specular);
		virtual ~Mesh() = default;

	public:
		virtual void Render() = 0;
		virtual void Update() = 0;
	};
}

#endif
