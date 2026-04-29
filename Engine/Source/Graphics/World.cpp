#include "World.h"

Engine::World::World(Core::App& app)
	: Scene(app), objects(), lights(), camera(app.window->GetWindow(), glm::vec3(5.0f, 5.0f, 5.0f)),
	shader(ProjectDirectory "/Resource/Shader/Cube.vert", ProjectDirectory "/Resource/Shader/Cube.frag")
{
	auto cube = std::make_unique<Cube>(shader);
	cube->name = "Brick cube";
	cube->transform.position = glm::vec3(-2.5f, 0.0f, 0.0f);

	auto plane = std::make_unique<Plane>(shader);
	plane->name = "Brick plane";
	plane->transform.position = glm::vec3(2.5f, 0.0f, 0.0f);

	objects.emplace_back(std::move(cube));
	objects.emplace_back(std::move(plane));

	auto light = std::make_unique<Light>();
	light->name = "Point light";
	light->transform.position = glm::vec3(4.375f, 3.5f, -3.75f);
	light->transform.scale = glm::vec3(0.25f);

	lights.emplace_back(std::move(light));
}

Engine::World::~World()
{
}

void Engine::World::Render()
{
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition;

	for (auto& light : lights)
	{
		light->shader.Activate();
		glUniform4f(glGetUniformLocation(light->shader.programID, "color"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		lightPosition = light->transform.position;

		light->Render();
	}

	for (auto& mesh : objects)
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
	camera.UpdateMatrix(Camera::ProjectionMode::PERSPECTIVE, 70.0f, nearPlane, farPlane, 2.5f);
	camera.Input();

	for (auto& light : lights)
	{
		light->Update();
		glUniformMatrix4fv(glGetUniformLocation(light->shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(light->transform.GetMatrix()));
		camera.Matrix(light->shader, "cameraMatrix");
	}
	
	for (auto& mesh : objects)
	{
		mesh->shader.Activate();

		glUniformMatrix4fv(glGetUniformLocation(mesh->shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(mesh->transform.GetMatrix()));
		glUniform3f(glGetUniformLocation(mesh->shader.programID, "cameraPosition"), camera.position.x, camera.position.y, camera.position.z);
		
		camera.Matrix(mesh->shader, "cameraMatrix");

		mesh->Update();
	}
}
