#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <optional>

#include <glad/gl.h>

#include "App.h"

#include "Graphics/Scene/Scene.h"
#include "Graphics/Scene/Sample.h"
#include "Graphics/Scene/World.h"

namespace Engine
{
	enum class SceneType
	{
		SAMPLE,
		WORLD
	};

	class Engine
	{
	private:
		Core::App app;

		std::unique_ptr<Scene> scene;
		std::unique_ptr<Core::UserInterface> ui;

		Sample* sample;
		World* world;

		SceneType activeSceneType;

	public:
		Engine(const Core::AppData& appData, SceneType initialSceneType = SceneType::SAMPLE);
		virtual ~Engine();

		void Render();
		void Update();

		void SwitchScene(SceneType sceneType);

	private:
		std::unique_ptr<Scene> CreateScene(SceneType sceneType);
		void InitializeScene(SceneType sceneType);
	};
}

#endif
