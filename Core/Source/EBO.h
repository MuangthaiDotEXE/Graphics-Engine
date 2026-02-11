#pragma once

#ifndef EBO_H
#define EBO_H

#include <vector>

#include <glad/gl.h>

namespace Core
{
	class EBO
	{
	private:
		GLuint eboID;

	public:
		EBO(GLuint* indices, GLsizeiptr size);
		EBO(std::vector<GLuint>& indices);
		virtual ~EBO();

		void Bind();
		void Unbind();
	};
}

#endif
