#pragma once

#ifndef CORE_VAO_H
#define CORE_VAO_H

#include <glad/gl.h>

#include "VBO.h"

namespace Core
{
	class VAO
	{
	private:
		GLuint vaoID;

	public:
		VAO();
		virtual ~VAO();

		void LinkAttributes(VBO& vbo, GLuint index, GLuint size, GLenum type, GLsizeiptr stride, const void* pointer);
		void Bind();
		void Unbind();
	};
}

#endif
