#include "VAO.h"

Core::VAO::VAO()
{
	glGenVertexArrays(1, &vaoID);
}

Core::VAO::~VAO()
{
	glDeleteVertexArrays(1, &vaoID);
}

void Core::VAO::LinkAttributes(VBO& vbo, GLuint index, GLuint size, GLenum type, GLsizeiptr stride, const void* pointer)
{
	vbo.Bind();
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
	glEnableVertexAttribArray(index);
	vbo.Unbind();
}

void Core::VAO::Bind()
{
	glBindVertexArray(vaoID);
}

void Core::VAO::Unbind()
{
	glBindVertexArray(0);
}
