#include "Light.h"

GLfloat lightVertices[] =
{
	// position			
	-1.0f,  1.0f,  1.0f,   // left top front vertex
	 1.0f,  1.0f,  1.0f,   // right top front vertex
	 1.0f, -1.0f,  1.0f,   // left bottom front vertex
	-1.0f, -1.0f,  1.0f,   // right bottom front vertex

	 1.0f,  1.0f, -1.0f,   // left top back vertex
	-1.0f,  1.0f, -1.0f,   // right top back vertex
	-1.0f, -1.0f, -1.0f,   // right bottom back vertex
	 1.0f, -1.0f, -1.0f	   // left bottom back vertex
};

GLuint lightIndices[] =
{
	// Front face
	0, 1, 3,
	1, 2, 3,

	// Right face
	1, 4, 2,
	4, 7, 2,

	//Back face
	4, 5, 7,
	5, 6, 7,

	// Left face
	5, 0, 6,
	0, 3, 6,

	// Top face
	5, 4, 0,
	4, 1, 0,

	// Bottom face
	3, 2, 6,
	2, 7, 6
};

Engine::Light::Light()
	: shader(ProjectDirectory "/Resource/Shader/Light.vert", ProjectDirectory "/Resource/Shader/Light.frag"),
	vao(), vbo(lightVertices, sizeof(lightVertices)), ebo(lightIndices, sizeof(lightIndices))
{
	vao.Bind();
	vbo.Bind();
	ebo.Bind();

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

Engine::Light::~Light()
{
}

void Engine::Light::Render()
{
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Light::Update()
{
	shader.Activate();
	vao.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}
