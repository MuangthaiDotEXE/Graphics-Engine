#include "VBO.h"

Core::VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Core::VBO::VBO(std::vector<vertex>& vertices)
{
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);
}

Core::VBO::~VBO()
{
	glDeleteBuffers(1, &vboID);
}

void Core::VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void Core::VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
