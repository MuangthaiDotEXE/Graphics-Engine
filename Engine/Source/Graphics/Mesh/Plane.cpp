#include "Plane.h"

vertex planeVertices[] =
{
			// positions					// colors					 // textures			// normals
	vertex{ glm::vec3(-1.0f,  0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) },
	vertex{ glm::vec3( 1.0f,  0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) },
	vertex{ glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) },
	vertex{ glm::vec3(-1.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) }
};

GLuint planeIndices[] =
{
	// Plane
	0, 1, 3,
	1, 2, 3
};

std::vector<vertex> planeVerts(planeVertices, planeVertices + sizeof(planeVertices) / sizeof(vertex));
std::vector<GLuint> planeInds(planeIndices, planeIndices + sizeof(planeIndices) / sizeof(GLuint));

Engine::Plane::Plane()
	: Mesh(ProjectDirectory "/Resource/Shader/Plane.vert", ProjectDirectory "/Resource/Shader/Plane.frag", 
		planeVerts, planeInds)
{
	vao.Bind();
	vbo.Bind();
	ebo.Bind();

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttributes(vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.LinkAttributes(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

Engine::Plane::~Plane()
{
}

void Engine::Plane::Render()
{
	shader.Activate();

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Plane::Update()
{
	shader.Activate();
	vao.Bind();

	glDrawElements(GL_TRIANGLES, planeInds.size(), GL_UNSIGNED_INT, 0);
}
