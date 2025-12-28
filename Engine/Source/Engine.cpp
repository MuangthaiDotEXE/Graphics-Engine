#include "Engine.h"

Engine::Engine::Engine(const App::AppData& appData)
	: app(appData), mesh(), camera(app.window->GetSize(), glm::vec3(0.0f, 0.0f, 5.0f))
{
}

Engine::Engine::~Engine()
{
	mesh.~Mesh();

	app.~App();
}

void Engine::Engine::Render()
{
	app.Render();

	mesh.Render();
}

void Engine::Engine::Update()
{
	while (!app.window->ShouldClose())
	{
		app.Update();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		mesh.Update();

		camera.Inputs(app.window->GetWindow());
		camera.UpdateMatrix(app.window->GetWindow(), 70.0f, 0.0001f, 100.0f);
		camera.Matrix(mesh.shader, "cameraMatrix");
	}
}
