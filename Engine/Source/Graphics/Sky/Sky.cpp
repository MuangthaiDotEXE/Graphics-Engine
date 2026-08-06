#include "Sky.h"

GLfloat skyVertices[] =
{
	// positions
	 1.0f, -1.0f,  1.0f,    // Back face bottom left vertex
	-1.0f, -1.0f,  1.0f,    // Back face bottom right vertex
	-1.0f,  1.0f,  1.0f,    // Back face top right vertex
	 1.0f,  1.0f,  1.0f,    // Back face top left vertex

	-1.0f, -1.0f, -1.0f,    // Front face bottom right vertex
	 1.0f, -1.0f, -1.0f,    // Front face bottom left vertex
	 1.0f,  1.0f, -1.0f,    // Front face top left vertex
	-1.0f,  1.0f, -1.0f     // Front face top right vertex
};

GLuint skyIndices[] =
{
	// Right face
	5, 0, 3,
	3, 6, 5,

	// Left face
	1, 4, 7,
	7, 2, 1,

	// Top face
	3, 2, 7,
	7, 6, 3,

	// Bottom face
	5, 4, 1,
	1, 0, 5,

	// Back face
	0, 1, 2,
	2, 3, 0,

	// Front face
	4, 5, 6,
	6, 7, 4
};

Engine::Sky::Sky(std::optional<std::vector<std::string>> cubemaps)
	: shader(ProjectDirectory "/Resource/Shader/Sky/Sky.vert", ProjectDirectory "/Resource/Shader/Sky/Sky.frag"),
	vao(),
	vbo(skyVertices, sizeof(skyVertices)),
	ebo(skyIndices, sizeof(skyIndices)),
	cubemap(std::move(cubemaps), "cubemap")
{
	Initialize();
}

Engine::Sky::Sky(const Core::Shader& shader, std::optional<std::vector<std::string>> cubemaps)
	: shader(shader),
	vao(),
	vbo(skyVertices, sizeof(skyVertices)),
	ebo(skyIndices, sizeof(skyIndices)),
	cubemap(std::move(cubemaps), "cubemap")
{
	Initialize();
}

void Engine::Sky::Render()
{
}

void Engine::Sky::Update()
{
	vao.Bind();
	cubemap.Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}

void Engine::Sky::Initialize()
{
	vao.Bind();
	vbo.Bind();
	ebo.Bind();

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	vbo.Unbind();
	vao.Unbind();
	ebo.Unbind();
}
