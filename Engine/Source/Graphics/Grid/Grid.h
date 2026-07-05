#pragma once

#ifndef GRID_H
#define GRID_H

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/VAO.h"
#include "Graphics/Shader/VBO.h"

namespace Engine
{
	class Grid
	{
	public:
		Core::Shader shader;
		Core::VAO vao;
		Core::VBO vbo;

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		float nearPlane = 0.001f, farPlane = 1000.0f;

	public:
		Grid();
		Grid(const Core::Shader& shader);
		virtual ~Grid() = default;

		void Render();
		void Update();
	
	private:
		void Initialize();
	};
}

#endif
