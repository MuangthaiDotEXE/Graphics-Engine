#include "VAO.h"

App::VAO::VAO()
{
	glGenVertexArrays(1, &vaoID);
}

App::VAO::~VAO()
{
	glDeleteVertexArrays(1, &vaoID);
}

void App::VAO::LinkAttributes(VBO& vbo, GLuint layout, GLuint numberOfComponents, GLenum type, GLsizeiptr stride, const void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, numberOfComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void App::VAO::Bind()
{
	glBindVertexArray(vaoID);
}

void App::VAO::Unbind()
{
	glBindVertexArray(0);
}
