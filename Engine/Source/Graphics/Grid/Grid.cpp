#include "Grid.h"

static GLfloat gridVertices[] =
{
	// Position
	-1.0f, -1.0f,
	 1.0f, -1.0f,
	 1.0f,  1.0f,
	-1.0f, -1.0f,
	 1.0f,  1.0f,
	-1.0f,  1.0f
};

Engine::Grid::Grid()
	: shader(ProjectDirectory "/Resource/Shader/Grid.vert", ProjectDirectory "/Resource/Shader/Grid.frag"),
	vao(),  vbo(gridVertices, sizeof(gridVertices))
{
	Initialize();
}

Engine::Grid::Grid(const Core::Shader& shader)
	: shader(shader),
	vao(), vbo(gridVertices, sizeof(gridVertices))
{
	Initialize();
}

void Engine::Grid::Render()
{
	shader.Activate();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Engine::Grid::Update()
{
	shader.Activate();
	vao.Bind();

	glUniformMatrix4fv(glGetUniformLocation(shader.programID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(glGetUniformLocation(shader.programID, "nearPlane"), nearPlane);
	glUniform1f(glGetUniformLocation(shader.programID, "farPlane"), farPlane);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	vao.Unbind();
	glDisable(GL_BLEND);
}

void Engine::Grid::Initialize()
{
	vao.Bind();
	vbo.Bind();

	vao.LinkAttributes(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);

	vbo.Unbind();
	vao.Unbind();
}
