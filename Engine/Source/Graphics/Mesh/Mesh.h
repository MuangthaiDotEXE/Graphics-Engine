#pragma once

#ifndef MESH_H
#define MESH_H

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		App::Shader shader;

	private:
		App::VAO vao;
		App::VBO vbo;
		App::EBO ebo;
		App::Texture texture;
		GLuint* textures;

	public:
		Mesh();
		virtual ~Mesh();

		void Render();
		void Update();
	};
}

#endif
