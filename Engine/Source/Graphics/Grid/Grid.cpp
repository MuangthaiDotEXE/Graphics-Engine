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

Engine::Grid::Grid(float nearPlane, float farPlane)
	: shader(ProjectDirectory "/Resource/Shader/Grid/Grid.vert", ProjectDirectory "/Resource/Shader/Grid/Grid.frag"),
	vao(),  
	vbo(gridVertices, sizeof(gridVertices)),
	nearPlane(nearPlane),
	farPlane(farPlane)
{
	Initialize();
}

Engine::Grid::Grid(const Core::Shader& shader, float nearPlane, float farPlane)
	: shader(shader),
	vao(), 
	vbo(gridVertices, sizeof(gridVertices)),
	nearPlane(nearPlane),
	farPlane(farPlane)
{
	Initialize();
}

void Engine::Grid::Render()
{
}

void Engine::Grid::Update()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

void Engine::Grid::SetView(glm::mat4 view)
{
	this->view = view;
}

void Engine::Grid::SetProjection(glm::mat4 projection)
{
	this->projection = projection;
}

void Engine::Grid::SetNearPlane(float nearPlane)
{
	this->nearPlane = nearPlane;
}

void Engine::Grid::SetFarPlane(float farPlane)
{
	this->farPlane = farPlane;
}

void Engine::Grid::Initialize()
{
	vao.Bind();
	vbo.Bind();

	vao.LinkAttributes(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);

	vbo.Unbind();
	vao.Unbind();
}
