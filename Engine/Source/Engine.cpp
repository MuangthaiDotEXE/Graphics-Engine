#include "Engine.h"

Engine::Engine::Engine(const Core::AppData& appData)
	: app(appData), world(app), ui(app.title, app.version, app.api, app.window->GetWindow())
{
}

Engine::Engine::~Engine()
{
}

void Engine::Engine::Render()
{
	app.Render();
	ui.Render();
	world.Render();
}

void Engine::Engine::Update()
{
	while (!app.window->ShouldClose())
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		ui.BeginFrame();
		ui.Update();
		world.Update();
		ui.EndFrame();

		app.Update();
	}
}
