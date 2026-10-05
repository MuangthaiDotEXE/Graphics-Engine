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
		ui->coordinate = scene->GetCamera().GetPosition();
		
		ui->Update();
		//ui->ViewportWindow(scene->GetViewportTexture(), scene->GetViewportSize());
		scene->Update();

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
	case SceneType::SPACE: return std::make_unique<Space>(app);
	}

	return nullptr;
}

void Engine::Engine::InitializeScene(SceneType sceneType)
{
	activeSceneType = sceneType;
	scene = CreateScene(sceneType);
	ui = std::make_unique<UserInterface::Default>(app.window.get(), app.title, app.version, app.GetGraphicsAPI(), scene->skyColor);

	sample = dynamic_cast<Sample*>(scene.get());
	world = dynamic_cast<World*>(scene.get());
	space = dynamic_cast<Space*>(scene.get());
}
