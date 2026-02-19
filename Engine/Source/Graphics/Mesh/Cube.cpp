#include "Cube.h"

vertex cubeVertices[] =
{
	vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },
	vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },
	vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },
	vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },

	vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },
	vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },
	vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },
	vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },

	vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },
	vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },
	vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },
	vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },

	vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },
	vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },
	vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },
	vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },

	vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  1.0f,  0.0f) },
	vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  1.0f,  0.0f) },
	vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f) },
	vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f) },

	vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },
	vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },
	vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },
	vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f) }


};

GLuint cubeIndices[] =
{
	// Front face
	 0,  1,  3,
	 1,  2,  3,

	// Right face
	 4,  5,  7,
	 5,  6,  7,

	// Back face
	 8,  9, 11,
	 9, 10, 11,

	// Left face
	12, 13, 15,
	13, 14, 15,

	// Top face
	16, 17, 19,
	17, 18, 19,

	// Bottom face
	20, 21, 23,
	21, 22, 23
};

std::vector<vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(vertex));
std::vector<GLuint> cubeInds(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));

Engine::Cube::Cube()
	: Mesh(ProjectDirectory "/Resource/Shader/Cube.vert", ProjectDirectory "/Resource/Shader/Cube.frag", 
		cubeVerts, cubeInds)
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

Engine::Cube::~Cube()
{
}

void Engine::Cube::Render()
{
	shader.Activate();

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Cube::Update()
{
	shader.Activate();
	vao.Bind();

	glDrawElements(GL_TRIANGLES, cubeInds.size(), GL_UNSIGNED_INT, 0);
}
