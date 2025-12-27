#include "Engine.h"

Engine::Engine::Engine(const App::AppData& appData)
	: app(appData)
{
}

Engine::Engine::~Engine()
{
	app.~App();
}

void Engine::Engine::Render()
{
	app.Render();
}

void Engine::Engine::Update()
{
	while (!app.window->ShouldClose())
	{
		app.Update();
	}
}
