#include "VBO.h"

Engine::VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Engine::VBO::~VBO()
{
	glDeleteBuffers(1, &vboID);
}

void Engine::VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void Engine::VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
