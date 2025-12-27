#pragma once

#ifndef APP_H
#define APP_H

#include <memory>
#include <assert.h>
#include <chrono>
#include <string>

#include "Window.h"
#include "Graphics.h"

namespace App
{
	struct AppData
	{
		std::string name = "App";
		WindowData windowData;
	};

	class App
	{
	private:
		AppData data;
		bool running;

		/* TODO: Add FPS system
		using clock = std::chrono::steady_clock;
		using timePoint = clock::time_point;
		using durationMilliseconds = std::chrono::milliseconds;
		*/

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
