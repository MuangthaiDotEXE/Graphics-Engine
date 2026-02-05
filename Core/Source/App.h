#pragma once

#ifndef APP_H
#define APP_H

#include <array>
#include <memory>
#include <assert.h>
#include <chrono>
#include <string>
#include <print>
#include <format>
#include <optional>

#include "Window.h"
#include "Graphics.h"
#include "OpenGL.h"
#include "Vulkan.h"
#include "UserInterface.h"

namespace Core
{
	struct AppData
	{
		WindowData windowData;
		GraphicsAPI graphicsAPI;
		std::string name = "App";
		std::array<int, 3> version;
	};
	
	class App
	{
	private:
		AppData data;
		bool running;

	public:
		std::unique_ptr<Window> window;
		std::unique_ptr<Graphics> graphics;
		std::optional<UserInterface> ui;

	public:
		App(const AppData& appData);
		virtual ~App();

		void Render();
		void Update();

		static App& GetApplication();
	};
}

#endif
