#include "Engine.h"

Engine::Engine::Engine(const Core::AppData& appData)
	: app(appData)
{
	scene = std::make_unique<Sample>(app);

	sample = dynamic_cast<Sample*>(scene.get());
	if (sample)
	{
		ui = std::make_unique<Core::UserInterface>(app.window.get(), app.title, app.version, app.GetGraphicsAPI(), sample->skyColor);
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

		if (sample)
		{
			ui->coordinate = sample->camera.GetPosition();
			//ui->ViewportWindow(world->GetViewportTexture(), world->GetViewportSize());
		}

		ui->EndFrame();
		app.Update();
	}
}
