#include "Engine.h"

Engine::Engine::Engine(const Core::AppData& appData)
	: app(appData), world(app), ui(app.window->GetWindow())
{
}

Engine::Engine::~Engine()
{
}

void Engine::Engine::Render()
{
	app.Render();
	world.Render();
	ui.Render();
}

void Engine::Engine::Update()
{
	while (!app.window->ShouldClose())
	{
		app.Update();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		world.Update();
		ui.Update();
	}
}
