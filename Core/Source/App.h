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

#include <glad/gl.h>

#include "Window/Window.h"
#include "Graphics/Graphics.h"
#include "Graphics/OpenGL.h"
#include "Graphics/Vulkan.h"
#include "UserInterface/UserInterface.h"

namespace Core
{
	struct AppData
	{
		WindowData windowData;
		GraphicsAPI graphicsAPI;
		int buildNumber = 1;
		std::string name = "App";
		std::string subVersion = "";
		std::array<unsigned int, 3> version;
	};
	
	class App
	{
	private:
		AppData data;
		bool running;

	public:
		std::unique_ptr<Window> window;
		std::unique_ptr<Graphics> graphics;

	public:
		App(const AppData& appData);
		virtual ~App();

		void Render();
		void Update();

		static App& GetApplication();
	};
}

#endif
