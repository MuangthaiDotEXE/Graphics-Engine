#include "VAO.h"

Core::VAO::VAO()
{
	glGenVertexArrays(1, &vaoID);
}

Core::VAO::~VAO()
{
	glDeleteVertexArrays(1, &vaoID);
}

void Core::VAO::LinkAttributes(VBO& vbo, GLuint layout, GLuint numberOfComponents, GLenum type, GLsizeiptr stride, const void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, numberOfComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
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
