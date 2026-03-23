#include "World.h"

Engine::World::World(Core::App& app)
	: app(app), object(), light(), camera(app.window->GetFramebufferSize(), glm::vec3(0.0f, 0.0f, 5.0f)),
	shader(ProjectDirectory "/Resource/Shader/Cube.vert", ProjectDirectory "/Resource/Shader/Cube.frag")
{
	auto cube = std::make_unique<Cube>(shader);
	cube->name = "Brick cube";
	cube->transform.position = glm::vec3(-2.5f, 0.0f, 0.0f);

	auto plane = std::make_unique<Plane>(shader);
	plane->name = "Brick plane";
	plane->transform.position = glm::vec3(2.5f, 0.0f, 0.0f);

	object.emplace_back(std::move(cube));
	object.emplace_back(std::move(plane));
}

Engine::World::~World()
{
}

void Engine::World::Render()
{
	glm::mat4 lightModel = glm::mat4(1.0f);
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition = glm::vec3(5.0f, 5.0f, 3.75f);
	lightModel = glm::translate(lightModel, lightPosition);
	lightModel = glm::scale(lightModel, glm::vec3(0.25f));

	light.shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(light.shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(light.shader.programID, "color"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	light.Render();

	for (auto& mesh : object)
	{
		mesh->shader.Activate();
		
		glUniform4f(glGetUniformLocation(mesh->shader.programID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(mesh->shader.programID, "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
		glUniform1f(glGetUniformLocation(mesh->shader.programID, "nearPlane"), nearPlane);
		glUniform1f(glGetUniformLocation(mesh->shader.programID, "farPlane"), farPlane);

		mesh->Render();
	}
}

void Engine::World::Update()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	camera.UpdateMatrix(app.window->GetWindow(), 70.0f, nearPlane, farPlane);
	camera.Inputs(app.window->GetWindow());

	light.Update();
	camera.Matrix(light.shader, "cameraMatrix");
	
	for (auto& mesh : object)
	{
		mesh->shader.Activate();

		glUniformMatrix4fv(glGetUniformLocation(mesh->shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(mesh->transform.GetMatrix()));
		glUniform3f(glGetUniformLocation(mesh->shader.programID, "cameraPosition"), camera.position.x, camera.position.y, camera.position.z);
		
		camera.Matrix(mesh->shader, "cameraMatrix");

		mesh->Update();
	}
}
