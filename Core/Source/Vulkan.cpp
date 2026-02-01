#include "Vulkan.h"

Core::Vulkan::Vulkan()
{
}

Core::Vulkan::~Vulkan()
{
	vkDestroyInstance(instance, nullptr);
}

void Core::Vulkan::Render()
{
}

void Core::Vulkan::Update()
{
}

void Core::Vulkan::ViewportResize(GLFWwindow* window)
{
}

void Core::Vulkan::CreateInstance()
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "App";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Graphics Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
}
