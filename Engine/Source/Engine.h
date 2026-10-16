#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <optional>
#include <vector>

#include <glad/gl.h>

#include "UserInterface/UserInterface.h"
#include "UserInterface/Layer.h"
#include "App.h"

#include "Graphics/Scene/Scene.h"
#include "Graphics/Scene/Sample.h"
#include "Graphics/Scene/World.h"
#include "Graphics/Scene/Space.h"
#include "UserInterface/Default.h"
#include "UserInterface/Hierarchy.h"

namespace Engine
{
	enum class SceneType
	{
		SAMPLE,
		WORLD,
		SPACE
	};

	class Engine
	{
	private:
		Core::App app;
		Core::UserInterface::Layer uiLayer;

		std::unique_ptr<Scene> scene;
		std::vector<std::unique_ptr<Core::UserInterface::UserInterface>> uis;
		UserInterface::Default* defaultUI = nullptr;

		Sample* sample;
		World* world;
		Space* space;

		SceneType activeSceneType;

	public:
		Engine(const Core::AppData& appData, SceneType initialSceneType = SceneType::SAMPLE);
		virtual ~Engine();

		void Render();
		void Update();

		void SwitchScene(SceneType sceneType);
		void CreateUIs();

	private:
		std::unique_ptr<Scene> CreateScene(SceneType sceneType);
		void InitializeScene(SceneType sceneType);
	};
}

#endif
