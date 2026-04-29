#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <optional>

#include <glad/gl.h>

#include "App.h"

#include "Graphics/Scene.h"
#include "Graphics/World.h"


namespace Engine
{
	class Engine
	{
	private:
		Core::App app;

		std::unique_ptr<Scene> scene;
		std::unique_ptr<Core::UserInterface> ui;

	public:
		Engine(const Core::AppData& appData);
		virtual ~Engine();

		void Render();
		void Update();
	};
}

#endif
