#include "UserInterface.h"

Core::UserInterface::UserInterface::UserInterface(Window* window, 
	const std::string& title, 
	const std::string& version, 
	const std::string& graphicsAPI, 
	const glm::vec3& skyColor
)
	: window(window), 
	title(title), 
	version(version), 
	skyColor(skyColor), 
	graphicsAPI(graphicsAPI), 
	vSync(window->GetMonitorSync())
{
}
