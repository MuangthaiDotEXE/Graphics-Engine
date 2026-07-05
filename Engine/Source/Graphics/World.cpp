#include "World.h"

Engine::World::World(Core::App& app)
	: Scene(app), grid(), objects(), lights(), 
	camera(app.window->GetWindow(), Camera::ProjectionMode::PERSPECTIVE, Camera::RotationMode::EULER, glm::vec3(8.75f, 8.75f, 8.75f)),
	shader(ProjectDirectory "/Resource/Shader/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh.frag"),
	fbo(app.window->GetFramebufferSize())
{
	auto cube = std::make_unique<Cube>(shader);
	cube->name = "Cube";
	cube->transform.position = glm::vec3(-5.0f, 0.0f, 0.0f);
	objects.emplace_back(std::move(cube));

	auto sphere = std::make_unique<Sphere>(shader);
	sphere->name = "Sphere";
	sphere->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	objects.emplace_back(std::move(sphere));

	auto pyramid = std::make_unique<Pyramid>(shader);
	pyramid->name = "Pyramid";
	pyramid->transform.position = glm::vec3(0.0f, 0.0f, -5.0f);
	objects.emplace_back(std::move(pyramid));

	auto plane = std::make_unique<Plane>(shader);
	plane->name = "Plane";
	plane->transform.position = glm::vec3(5.0f, 0.0f, 0.0f);
	objects.emplace_back(std::move(plane));

	auto light = std::make_unique<Light>();
	light->name = "Point light";
	light->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	light->transform.position = glm::vec3(4.375f, 3.5f, -3.75f);
	light->transform.scale = glm::vec3(0.25f);
	lights.emplace_back(std::move(light));
}

Engine::World::~World()
{
}

void Engine::World::Render()
{
	glm::vec4 lightColor = glm::vec4(0.0f);
	glm::vec3 lightPosition = glm::vec3(0.0f);

	for (auto& light : lights)
	{
		light->shader.Activate();

		glUniform4f(glGetUniformLocation(light->shader.programID, "color"), light->color.r, light->color.g, light->color.b, light->color.w);

		lightColor = light->color;
		lightPosition = light->transform.position;

		light->Render();
	}

	for (auto& mesh : objects)
	{
		mesh->shader.Activate();
		
		glUniform4f(glGetUniformLocation(mesh->shader.programID, "lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.w);
		glUniform3f(glGetUniformLocation(mesh->shader.programID, "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
		glUniform1f(glGetUniformLocation(mesh->shader.programID, "nearPlane"), nearPlane);
		glUniform1f(glGetUniformLocation(mesh->shader.programID, "farPlane"), farPlane);

		mesh->Render();
	}

	grid.Render();
}

void Engine::World::Update()
{
	//glm::vec2 windowSize = app.window->GetFramebufferSize();
	//fbo.Resize(windowSize);

	//fbo.Bind();

	camera.UpdateMatrix(70.0f, nearPlane, farPlane, 2.5f);
	camera.Input();

	for (auto& light : lights)
	{
		light->shader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(light->shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(light->transform.GetMatrix()));
		
		camera.Matrix(light->shader, "cameraMatrix");

		light->Update();
	}
	
	for (auto& mesh : objects)
	{
		mesh->shader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(mesh->shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(mesh->transform.GetMatrix()));
		
		glUniform3f(glGetUniformLocation(mesh->shader.programID, "cameraPosition"), camera.position.x, camera.position.y, camera.position.z);
		camera.Matrix(mesh->shader, "cameraMatrix");

		mesh->Update();
	}

	grid.view = camera.GetView();
	grid.projection = camera.GetProjection();
	grid.nearPlane = nearPlane;
	grid.farPlane = farPlane;
	grid.Update();

	//fbo.Unbind();
}

GLuint Engine::World::GetViewportTexture() const
{
	return fbo.GetColorTexture();
}

glm::vec2 Engine::World::GetViewportSize() const
{
	return fbo.GetSize();
}
