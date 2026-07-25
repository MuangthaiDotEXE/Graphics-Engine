#include <cstdio>
#include <print>
#include <chrono>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Engine.h"
#include "Timer/Timer.h"

int main(int argc, char** argv)
{
#ifdef _WIN32
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwordMode = 0;

	GetConsoleMode(handleOut, &dwordMode);
	dwordMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	SetConsoleMode(handleOut, dwordMode);
#endif

	Engine::Timer initializeTime, appTime;

	Core::AppData engineData{};
	engineData.appName = "Graphics Engine";
	engineData.engineName = "Graphics Engine";
	engineData.version = { 1, 0, 0 };
	engineData.developmentStage = Core::AppData::DevelopmentStage::ALPHA;
	engineData.buildNumber = 1;
	engineData.windowData.width = 854u;
	engineData.windowData.height = 480u;
	engineData.windowData.fullscreen = false;
	engineData.windowData.icon = ProjectDirectory "/Asset/Icon/Icon.png";
	engineData.graphicsAPI = Core::GraphicsAPI::OPENGL;

	try
	{
		for (size_t i = 0; i < argc; i++)
		{
			if (std::string(argv[i]) == "-opengl")
			{
				engineData.graphicsAPI = Core::GraphicsAPI::OPENGL;
			}
			else if (std::string(argv[i]) == "-vulkan")
			{
				engineData.graphicsAPI = Core::GraphicsAPI::VULKAN;
			}

			if (std::string(argv[i]) == "--reset-window" && std::filesystem::exists("Window.state"))
			{
				std::filesystem::remove("Window.state");
			}

			if (std::string(argv[i]) == "--console")
			{
				// Add console window controlling
			}
		}

		Engine::Engine engine(engineData);

		initializeTime.Stop();
#ifndef NDEBUG
		std::print(stdout, "\n\033[0m[Debug] Application finished initialization in {} ({})\033[0m\n\n", initializeTime.GetDurationInMilliseconds(), std::chrono::duration<double>(initializeTime.GetDurationInMilliseconds()));
#endif

		engine.Render();
		engine.Update();
	}
	catch (const std::exception& exception)
	{
		std::print(stderr, "\033[31m[Error] An exception was thrown: {}\033[0m\n", exception.what());

		return 1;
	}

	appTime.Stop();
#ifndef NDEBUG
	std::print(stdout, "\n\033[0m[Debug] Application finished running in {} ({})\033[0m\n", appTime.GetDurationInMilliseconds(), std::chrono::duration<double>(appTime.GetDurationInMilliseconds()));
#endif

	return 0;
}
