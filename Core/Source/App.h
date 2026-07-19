#pragma once

#ifndef APP_H
#define APP_H

#include <cstdio>
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
		GraphicsAPI graphicsAPI = GraphicsAPI::OPENGL;

		int buildNumber = 1;
		std::string appName = "App";
		std::string engineName = "Engine";
		std::string subVersion = "";
		std::array<unsigned int, 3> version = { 1, 0, 0 };

		enum struct DevelopmentStage
		{
			ALPHA,
			BETA,
			RELEASE_CANDIDATE,
			RELEASE
		};
		DevelopmentStage developmentStage = DevelopmentStage::ALPHA;
	};
	
	class App
	{
	private:
		AppData appData;
		bool running;
		
	public:
		std::string title = "";
		std::string version = "";
		std::string api = "";

		std::string graphicsVendor = "";
		std::string graphicsRenderer = "";
		std::string graphicsVersion = "";
		std::string graphicsShadingLanguage = "";

		std::unique_ptr<Window> window;
		std::unique_ptr<Graphics> graphics;

	public:
		App(const AppData& appData = AppData());
		virtual ~App();

		void Render();
		void Update();

		std::string GetConfigurations();
		std::string GetGraphicsAPI();
		void PrintGraphicsInformation();
		std::string GetDevelopmentStage();

		static App& GetApplication();
		void Quit();
	};
}

#endif
