#include "Engine.h"

Engine::Engine::Engine(const Core::AppData& appData)
	: app(appData)
{
	scene = std::make_unique<World>(app);

	world = dynamic_cast<World*>(scene.get());
	if (world)
	{
		ui = std::make_unique<Core::UserInterface>(app.window.get(), app.title, app.version, app.GetGraphicsAPI(), world->skyColor);
	}
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
		ui->BeginFrame();
		ui->Update();

		scene->Update();

		if (world)
		{
			ui->coordinate = world->camera.GetPosition();
			//ui->ViewportWindow(world->GetViewportTexture(), world->GetViewportSize());
		}

		ui->EndFrame();
		app.Update();
	}
}
