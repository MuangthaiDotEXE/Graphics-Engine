#pragma once

#ifndef APP_H
#define APP_H

#include <array>
#include <memory>
#include <assert.h>
#include <chrono>
#include <string>
#include <format>

#include "Window.h"
#include "Graphics.h"

namespace Core
{
	struct AppData
	{
		std::string name = "App";
		std::array<int, 3> version = { 0, 0, 0 };
		WindowData windowData;
	};
	
	class App
	{
	private:
		AppData data;
		bool running;

	public:
		std::unique_ptr<Window> window;
		Graphics graphics;

	public:
		App(const AppData& appData);
		virtual ~App();

		void Render();
		void Update();

		static App& GetApplication();
	};
}

#endif
