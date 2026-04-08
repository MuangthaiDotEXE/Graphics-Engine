#pragma once

#ifndef VBO_H
#define VBO_H

#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 textureUV;
	glm::vec3 normal;
};

namespace Core
{
	class VBO
	{
	private:
		GLuint vboID;

	public:
		VBO(GLfloat* vertices, GLsizeiptr size);
		VBO(std::vector<Vertex>& vertices);
		virtual ~VBO();

		void Bind();
		void Unbind();
	};
}

#endif
