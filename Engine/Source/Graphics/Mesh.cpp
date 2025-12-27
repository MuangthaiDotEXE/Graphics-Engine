#include "Mesh.h"

GLfloat vertices[] =
{
	 0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
};

GLuint indices[] =
{
	0, 1, 2
};

Engine::Mesh::Mesh()
	: shader("", ""), vao(), vbo(vertices, sizeof(vertices)), ebo(indices, sizeof(indices))
{
}

Engine::Mesh::~Mesh()
{
}

void Engine::Mesh::Render()
{
}

void Engine::Mesh::Update()
{
}
