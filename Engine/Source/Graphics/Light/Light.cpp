#include "Light.h"

vertex lightVertices[] =
{
			// positions
	vertex{ glm::vec3(-1.0f,  1.0f,  1.0f) },   // top left front vertex
	vertex{ glm::vec3( 1.0f,  1.0f,  1.0f) },	// top right front vertex
	vertex{ glm::vec3( 1.0f, -1.0f,  1.0f) },	// bottom right front vertex
	vertex{ glm::vec3(-1.0f, -1.0f,  1.0f) },	// bottom left front vertex

	vertex{ glm::vec3( 1.0f,  1.0f, -1.0f) },   // top left back vertex
	vertex{ glm::vec3(-1.0f,  1.0f, -1.0f) },	// top right back vertex
	vertex{ glm::vec3(-1.0f, -1.0f, -1.0f) },	// bottom right back vertex
	vertex{ glm::vec3( 1.0f, -1.0f, -1.0f) }    // bottom left back vertex
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

std::vector<vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(vertex));
std::vector<GLuint> lightInds(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

Engine::Light::Light()
	: shader(ProjectDirectory "/Resource/Shader/Light.vert", ProjectDirectory "/Resource/Shader/Light.frag"),
	vao(), vbo(lightVerts), ebo(lightInds)
{
	vao.Bind();
	vbo.Bind();
	ebo.Bind();

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, sizeof(vertex), (void*)0);

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
