#include "Engine.h"

Engine::Engine::Engine(const Core::AppData& appData, SceneType initialSceneType)
	: app(appData), uiLayer(app.window.get())
{
	InitializeScene(initialSceneType);
	CreateUIs();
}

Engine::Engine::~Engine()
{
}

void Engine::Engine::Render()
{
	app.Render();

	for (auto& ui : uis)
	{
		ui->Render();
	}
		
	scene->Render();
}

void Engine::Engine::Update()
{
	while (!app.window->ShouldClose())
	{
		uiLayer.Start();
		scene->Update();

		if (defaultUI)
		{
			defaultUI->SetCameraPosition(scene->GetCamera().GetPosition());
		}

		for (auto& ui : uis)
		{
			ui->Update();
		}

		uiLayer.End();
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

void Engine::Engine::CreateUIs()
{
	auto uiDefault = std::make_unique<UserInterface::Default>(
		app.window.get(),
		app.appData.GetTitle(),
		app.appData.GetVersion(),
		app.GetGraphicsAPI(),
		scene->skyColor
	);
	defaultUI = uiDefault.get();
	uis.emplace_back(std::move(uiDefault));

	uis.emplace_back(std::make_unique<UserInterface::Hierarchy>(app.window.get()));
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

	sample = dynamic_cast<Sample*>(scene.get());
	world = dynamic_cast<World*>(scene.get());
	space = dynamic_cast<Space*>(scene.get());
}
