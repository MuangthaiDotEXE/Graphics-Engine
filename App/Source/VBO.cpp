#include "VBO.h"

App::VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

App::VBO::~VBO()
{
	glDeleteBuffers(1, &vboID);
}

void App::VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void App::VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
