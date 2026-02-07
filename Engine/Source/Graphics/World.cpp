#include "World.h"

Engine::World::World(Core::App& app)
	: app(app), mesh(), light(), camera(app.window->GetFramebufferSize(), glm::vec3(0.0f, 0.0f, 5.0f))
{
}

Engine::World::~World()
{
}

void Engine::World::Render()
{
	glm::mat4 meshModel = glm::mat4(1.0f);
	meshModel = glm::translate(meshModel, glm::vec3(0.0f, 0.0f, 0.0f));
	meshModel = glm::scale(meshModel, glm::vec3(1.0f));
	meshModel = glm::rotate(meshModel, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition = glm::vec3(2.5f, 2.5f, 2.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPosition);
	lightModel = glm::scale(lightModel, glm::vec3(0.25f));

	mesh.shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(mesh.shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(meshModel));
	glUniform4f(glGetUniformLocation(mesh.shader.programID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(mesh.shader.programID, "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);

	light.shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(light.shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(light.shader.programID, "color"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	mesh.Render();
	light.Render();
}

void Engine::World::Update()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	camera.UpdateMatrix(app.window->GetWindow(), 70.0f, 0.001f, 1000.0f);
	camera.Inputs(app.window->GetWindow());
	
	mesh.Update();
	glUniform3f(glGetUniformLocation(mesh.shader.programID, "cameraPosition"), camera.position.x, camera.position.y, camera.position.z);
	camera.Matrix(mesh.shader, "cameraMatrix");

	light.Update();
	camera.Matrix(light.shader, "cameraMatrix");
}
