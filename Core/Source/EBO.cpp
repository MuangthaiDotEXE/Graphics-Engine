#include "EBO.h"

Core::EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

Core::EBO::~EBO()
{
	glDeleteBuffers(1, &eboID);
}

void Core::EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
}

void Core::EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
