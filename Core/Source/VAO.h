#pragma once

#ifndef VAO_H
#define VAO_H

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

		void LinkAttributes(VBO& vbo, GLuint layout, GLuint numberOfComponents, GLenum type, GLsizeiptr stride, const void* offset);
		void Bind();
		void Unbind();
	};
}

#endif
