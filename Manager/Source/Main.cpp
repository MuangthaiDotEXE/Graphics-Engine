#include "Manager.h"

int main(int argc, char** argv)
{
	Core::AppData managerData;
	managerData.appName = "Project Manager";
	managerData.engineName = "No Engine";
	managerData.version = { 1, 0, 0 };
	managerData.subVersion = "";
	managerData.developmentStage = Core::AppData::DevelopmentStage::Alpha;
	managerData.buildNumber = 1;
	managerData.windowData.width = 854u;
	managerData.windowData.height = 480u;
	managerData.windowData.fullscreen = false;
	managerData.windowData.resizable = true;
	managerData.windowData.icon = ProjectDirectory "/Asset/Icon/Icon.png";
	managerData.graphicsAPI = Core::GraphicsAPI::OpenGL;

	try
	{
		Manager::Manager manager(managerData);

		manager.Render();
		manager.Update();
	}
	catch (const std::exception& exception)
	{
		Core::Log::Critical("Application", std::format("An exception was thrown: {}", exception.what()));

		return 1;
	}

	return 0;
}
