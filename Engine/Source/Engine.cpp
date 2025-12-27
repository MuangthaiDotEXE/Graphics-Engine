#include "Engine.h"

Engine::Engine::Engine(const App::AppData& appData)
	: app(appData), mesh()
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

		mesh.Update();
	}
}
