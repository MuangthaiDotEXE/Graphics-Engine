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

namespace Engine
{
	class Mesh
	{
	public:
		Shader shader;

	private:
		VAO vao;
		VBO vbo;
		EBO ebo;

	public:
		Mesh();
		virtual ~Mesh();

		void Render();
		void Update();
	};
}

#endif
