#pragma once

#ifndef VBO_H
#define VBO_H

#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

struct vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 textureUV;
};

namespace Core
{
	class VBO
	{
	private:
		GLuint vboID;

	public:
		VBO(GLfloat* vertices, GLsizeiptr size);
		VBO(std::vector<vertex>& vertices);
		virtual ~VBO();

		void Bind();
		void Unbind();
	};
}

#endif
