#include "Engine.h"

int main(int argc, char** argv)
{
	App::AppData engineData {};
	engineData.name = "Graphics Engine";
	engineData.windowData.width = 854u;
	engineData.windowData.height = 480u;

	Engine::Engine engine(engineData);
	engine.Render();
	engine.Update();
}
