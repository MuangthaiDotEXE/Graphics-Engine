#pragma once

#ifndef VBO_H
#define VBO_H

#include <glad/gl.h>

namespace App
{
	class VBO
	{
	private:
		GLuint vboID;

	public:
		VBO(GLfloat* vertices, GLsizeiptr size);
		virtual ~VBO();

		void Bind();
		void Unbind();
	};
}

#endif
