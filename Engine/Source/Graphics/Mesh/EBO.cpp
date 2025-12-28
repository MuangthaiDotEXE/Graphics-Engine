#include "EBO.h"

Engine::EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

Engine::EBO::~EBO()
{
	glDeleteBuffers(1, &eboID);
}

void Engine::EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
}

void Engine::EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
