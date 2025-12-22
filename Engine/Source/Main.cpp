#include "App.h"

int main(int argc, char** argv)
{
	App::AppData engineData {};
	engineData.name = "Graphics Engine";
	engineData.windowData.width = 854u;
	engineData.windowData.height = 480u;

	App::App engine(engineData);
	engine.Render();
	engine.Update();
}
