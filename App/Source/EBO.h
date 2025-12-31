#pragma once

#ifndef EBO_H
#define EBO_H

#include <glad/gl.h>

namespace App
{
	class EBO
	{
	private:
		GLuint eboID;

	public:
		EBO(GLuint* indices, GLsizeiptr size);
		virtual ~EBO();

		void Bind();
		void Unbind();
	};
}

#endif
