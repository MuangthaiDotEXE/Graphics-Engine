#include "EBO.h"

App::EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

App::EBO::~EBO()
{
	glDeleteBuffers(1, &eboID);
}

void App::EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
}

void App::EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
