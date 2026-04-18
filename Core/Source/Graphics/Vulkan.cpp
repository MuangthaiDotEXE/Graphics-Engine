#include "Vulkan.h"

Core::Vulkan::Vulkan()
{
	CreateInstance();
}

Core::Vulkan::~Vulkan()
{
	Cleanup();
}

void Core::Vulkan::Render()
{
}

void Core::Vulkan::Update()
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

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = 0;

	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
	{
		throw std::exception("Vulkan graphics API failed to create instance (Vulkan graphics API)\n");
	}
}

void Core::Vulkan::Cleanup()
{
	vkDestroyInstance(instance, nullptr);
}
