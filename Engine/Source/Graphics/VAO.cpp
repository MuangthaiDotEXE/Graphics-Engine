#include "VAO.h"

Engine::VAO::VAO()
{
	glGenVertexArrays(1, &vaoID);
}

Engine::VAO::~VAO()
{
	glDeleteVertexArrays(1, &vaoID);
}

void Engine::VAO::LinkAttributes(VBO& vbo, GLuint layout, GLuint numberOfComponents, GLenum type, GLsizeiptr stride, const void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, numberOfComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void Engine::VAO::Bind()
{
	glBindVertexArray(vaoID);
}

void Engine::VAO::Unbind()
{
	glBindVertexArray(0);
}
