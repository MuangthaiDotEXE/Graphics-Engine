#include "Mesh.h"

GLfloat vertices[] =
{
	// Positions          // Colors
	 0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
};

GLuint indices[] =
{
	// Triangle
	0, 1, 2
};

Engine::Mesh::Mesh()
	: shader(ProjectDirectory "/Resource/Shader/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh.frag"), vao(), vbo(vertices, sizeof(vertices)), ebo(indices, sizeof(indices))
{
	vao.Bind();
	vbo.Bind();
	ebo.Bind();

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

Engine::Mesh::~Mesh()
{
}

void Engine::Mesh::Render()
{
	glFrontFace(GL_CW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
}

void Engine::Mesh::Update()
{
	shader.Activate();
	vao.Bind();

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
}
