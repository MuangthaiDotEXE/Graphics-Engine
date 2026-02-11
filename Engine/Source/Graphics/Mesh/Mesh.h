#pragma once

#ifndef MESH_H
#define MESH_H

#include <memory>

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
	protected:
		std::unique_ptr<Core::Shader> shader;
		std::unique_ptr<Core::VAO> vao;
		std::unique_ptr<Core::VBO> vbo;
		std::unique_ptr<Core::EBO> ebo;

		std::vector<vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Core::Texture> textures;
		
	public:
		Mesh();
		virtual ~Mesh() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;
	};
}

#endif
