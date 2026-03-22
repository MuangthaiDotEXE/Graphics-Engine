#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <optional>

#include <glad/gl.h>

#include "App.h"

#include "Graphics/World.h"

namespace Engine
{
	class Engine
	{
	private:
		Core::App app;

		World world;
		Core::UserInterface ui;

	public:
		Engine(const Core::AppData& appData);
		virtual ~Engine();

		void Render();
		void Update();
	};
}

#endif
