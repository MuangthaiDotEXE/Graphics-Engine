#include <print>
#include <stdexcept>

#include "Engine.h"

int main(int argc, char** argv)
{
	Core::AppData engineData {};
	engineData.name = "Graphics Engine";
	engineData.version = { 1, 0, 0 };
	engineData.windowData.width = 854u;
	engineData.windowData.height = 480u;
	engineData.windowData.vSync = true;

	try
	{
		Engine::Engine engine(engineData);
		engine.Render();
		engine.Update();
	}
	catch (const std::exception& exception)
	{
		std::print("[Error] An exception was thrown: {}\n", exception.what());
		
		return 1;
	}
}
