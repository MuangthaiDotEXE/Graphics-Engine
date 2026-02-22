#pragma once

#ifndef MESH_H
#define MESH_H

#include <string>

#include <glad/gl.h>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

namespace Engine
{
	class Mesh
	{
	public:
		Core::Shader shader;
		Core::VAO vao;
		Core::VBO vbo;
		Core::EBO ebo;
		Core::Texture texture;
		Core::Texture specular;
		
		Mesh(const std::string& vertexShader, const std::string& fragmentShader, std::vector<vertex>& vertices, std::vector<GLuint>& indices, const Core::Texture& texture, const Core::Texture specular);
		virtual ~Mesh() = default;

	public:
		virtual void Render() = 0;
		virtual void Update() = 0;
	};
}

#endif
