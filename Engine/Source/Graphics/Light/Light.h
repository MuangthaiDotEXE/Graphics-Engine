#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/VAO.h"
#include "Graphics/Shader/VBO.h"
#include "Graphics/Shader/EBO.h"

namespace Engine
{
	class Light
	{
	public:
		Core::Shader shader;

	private:
		Core::VAO vao;
		Core::VBO vbo;
		Core::EBO ebo;

	public:
		Light();
		virtual ~Light();

		void Render();
		void Update();
	};
}

#endif
