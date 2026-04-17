#include <cstdio>
#include <print>
#include <stdexcept>

#include "Engine.h"

int main(int argc, char** argv)
{
	Core::AppData engineData {};
	engineData.name = "Graphics Engine";
	engineData.version = { 1, 0, 0 };
	engineData.buildNumber = 1;
	engineData.windowData.width = 854u;
	engineData.windowData.height = 480u;
	engineData.windowData.vSync = true;
	engineData.windowData.icon = ProjectDirectory "/Icon.png";
	engineData.graphicsAPI = Core::GraphicsAPI::OPENGL;

	try
	{
		Engine::Engine engine(engineData);

#if !defined(NDEBUG)
		for (size_t i = 0; i < argc; i++)
		{
			std::print(stdout, "[Debug] Arguments (argv[{}]): {}\n", i, argv[i]);
		}
#endif

		engine.Render();
		engine.Update();
	}
	catch (const std::exception& exception)
	{
		std::print(stderr, "\033[1;31m[Error] An exception was thrown: {}\033[0m\n", exception.what());
		
		return 1;
	}

	return 0;
}
