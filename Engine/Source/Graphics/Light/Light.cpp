#include "Light.h"

Vertex lightVertices[] =
{
			// positions
	Vertex{ glm::vec3(-1.0f,  1.0f,  1.0f) },   // top left front Vertex
	Vertex{ glm::vec3( 1.0f,  1.0f,  1.0f) },	// top right front Vertex
	Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f) },	// bottom right front Vertex
	Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f) },	// bottom left front Vertex

	Vertex{ glm::vec3( 1.0f,  1.0f, -1.0f) },   // top left back Vertex
	Vertex{ glm::vec3(-1.0f,  1.0f, -1.0f) },	// top right back Vertex
	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f) },	// bottom right back Vertex
	Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f) }    // bottom left back Vertex
};

GLuint lightIndices[] =
{
	// Front face
	0, 1, 2,
	0, 2, 3,

	// Back face
	4, 5, 6,
	4, 6, 7,

	// Right face
	1, 4, 7,
	1, 7, 2,

	// Left face
	5, 0, 3,
	5, 3, 6,

	// Top face
	5, 4, 1,
	5, 1, 0,

	// Bottom face
	3, 2, 7,
	3, 7, 6
};

std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
std::vector<GLuint> lightInds(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

Engine::Light::Light()
	: shader(ProjectDirectory "/Resource/Shader/Light.vert", ProjectDirectory "/Resource/Shader/Light.frag"),
	vao(), vbo(lightVerts), ebo(lightInds)
{
	vao.Bind();
	vbo.Bind();
	ebo.Bind();

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

Engine::Light::~Light()
{
}

void Engine::Light::Render()
{
	shader.Activate();
	
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Light::Update()
{
	shader.Activate();
	vao.Bind();

	glDrawElements(GL_TRIANGLES, lightInds.size(), GL_UNSIGNED_INT, 0);
}
