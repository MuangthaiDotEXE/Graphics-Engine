#include "Engine.h"

Engine::Engine::Engine(const Core::AppData& appData, SceneType initialSceneType)
	: app(appData)
{
	InitializeScene(initialSceneType);
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

		ui->coordinate = scene->GetCamera().GetPosition();
		//ui->ViewportWindow(scene->GetViewportTexture(), scene->GetViewportSize());
		

		ui->EndFrame();
		app.Update();
	}
}

void Engine::Engine::SwitchScene(SceneType sceneType)
{
	if (sceneType == activeSceneType)
	{
		return;
	}

	InitializeScene(sceneType);
}

std::unique_ptr<Engine::Scene> Engine::Engine::CreateScene(SceneType sceneType)
{
	switch (sceneType)
	{
	case SceneType::SAMPLE: return std::make_unique<Sample>(app);
	case SceneType::WORLD: return std::make_unique<World>(app);
	}

	return nullptr;
}

void Engine::Engine::InitializeScene(SceneType sceneType)
{
	activeSceneType = sceneType;
	scene = CreateScene(sceneType);

	sample = dynamic_cast<Sample*>(scene.get());
	world = dynamic_cast<World*>(scene.get());

	if (!ui)
	{
		ui = std::make_unique<Core::UserInterface>(app.window.get(), app.title, app.version, app.GetGraphicsAPI(), scene->skyColor);
	}
}
