#include "Engine.h"

Engine::Engine::Engine(const Core::AppData& appData)
	: app(appData)
{
	scene = std::make_unique<World>(app);
	ui = std::make_unique<Core::UserInterface>(app.window.get(), app.title, app.version, app.api);
}

Engine::Engine::~Engine()
{
}

void Engine::Engine::Render()
{
	app.Render();
	ui->Render();
	scene->Render();
}

void Engine::Engine::Update()
{
	while (!app.window->ShouldClose())
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		ui->BeginFrame();
		ui->Update();
		scene->Update();
		ui->EndFrame();

		app.Update();
	}
}
