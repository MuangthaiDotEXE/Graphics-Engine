#include <cstdio>
#include <print>
#include <chrono>
#include <stdexcept>

#include "Engine.h"

int main(int argc, char** argv)
{
	auto initializeStart = std::chrono::high_resolution_clock::now();
	auto appStart = std::chrono::high_resolution_clock::now();

	Core::AppData engineData {};
	engineData.name = "Graphics Engine";
	engineData.version = { 1, 0, 0 };
	engineData.developmentStage = Core::AppData::DevelopmentStage::ALPHA;
	engineData.buildNumber = 1;
	engineData.windowData.width = 854u;
	engineData.windowData.height = 480u;
	engineData.windowData.vSync = true;
	engineData.windowData.icon = ProjectDirectory "/Asset/Icon/Icon.png";
	engineData.graphicsAPI = Core::GraphicsAPI::OPENGL;
	
	try
	{
		Engine::Engine engine(engineData);

#ifndef NDEBUG
		for (size_t i = 0; i < argc; i++)
		{
			std::print(stdout, "[Debug] Arguments (argv[{}]): {}\n", i, argv[i]);
		}
#endif

		auto initializeFinish = std::chrono::high_resolution_clock::now();
		auto initializeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(initializeFinish - initializeStart);
#ifndef NDEBUG
		std::println(stdout, "\n\033[0m[Debug] Application finished initialization in {} ({})\033[0m\n", initializeDuration, std::chrono::duration<double>(initializeDuration));
#endif

		engine.Render();
		engine.Update();
	}
	catch (const std::exception& exception)
	{
		std::print(stderr, "\033[31m[Error] An exception was thrown: {}\033[0m\n", exception.what());
		
		return 1;
	}

	auto appFinish = std::chrono::high_resolution_clock::now();
	auto appDuration = std::chrono::duration_cast<std::chrono::milliseconds>(appFinish - appStart);
#ifndef NDEBUG
	std::print(stdout, "\n\033[0m[Debug] Application finished running in {} ({})\033[0m\n", appDuration, std::chrono::duration<double>(appDuration));
#endif

	return 0;
}
