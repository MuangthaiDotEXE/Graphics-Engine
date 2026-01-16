#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include <glad/gl.h>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

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
