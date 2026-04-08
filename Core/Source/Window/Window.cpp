#include "Window.h"

static void ErrorCallback(int error, const char* description)
{
	std::fprintf(stderr, "GLFW error %d: %s (GLFW windowing API)\n", error, description);
}

Core::Window::Window(const WindowData& windowData = WindowData(), GraphicsAPI graphicsAPI = GraphicsAPI::OPENGL)
	: data(windowData)
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize window (GLFW windowing API)\n");
	}

	if (graphicsAPI == GraphicsAPI::OPENGL)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
	}
	else if (graphicsAPI == GraphicsAPI::VULKAN)
	{
		if (!glfwVulkanSupported())
		{
			glfwTerminate();
			throw std::runtime_error("Vulkan graphics API is not supported (GLFW windowing API)\n");
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, data.resizable);
	glfwWindowHint(GLFW_DECORATED, data.decorated);

	window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
	if (window == nullptr || !window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window (GLFW windowing API)\n");
	}

	if (graphicsAPI == GraphicsAPI::OPENGL)
	{
		glfwMakeContextCurrent(window);

		glfwSwapInterval(data.vSync);
	}

	if (!data.icon.empty() && std::filesystem::exists(data.icon))
	{
		GLFWimage icon[1];
		int width, height, channels;

		unsigned char* image = stbi_load(data.icon.c_str(), &width, &height, &channels, STBI_rgb_alpha);

		if (image)
		{
			icon[0].width = width;
			icon[0].height = height;
			icon[0].pixels = image;

			glfwSetWindowIcon(window, 1, icon);

			stbi_image_free(image);
		}
		else
		{
			std::print("Failed to load icon: '{}'. Application will use operating system's default icon instead (GLFW windowing API)\n", data.icon);
		}
	}

	SetCenter();

	if (glfwRawMouseMotionSupported())
	{
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
}

Core::Window::~Window()
{
	if (window != nullptr)
	{
		glfwDestroyWindow(window);
	}

	glfwTerminate();
}

void Core::Window::Input()
{
	// Mouse
	{
		// Empty for now
	}

	// Keyboard
	{
		double currentTime = glfwGetTime();

		if (currentTime - toggleTime > debounceTime)
		{
			if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS)
			{
				Fullscreen();
				toggleTime = currentTime;
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(window, true);
				toggleTime = currentTime;
			}
		}
	}
}

void Core::Window::Render()
{
	glfwShowWindow(window);
}

void Core::Window::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Core::Window::ShouldClose() const
{
	return glfwWindowShouldClose(window);
}

GLFWwindow* Core::Window::GetWindow() const
{
	if (window == nullptr || !window)
	{
		throw std::runtime_error("Failed to return window because window does not exist (GLFW windowing API)");
	}

	return this->window;
}

glm::vec2 Core::Window::GetWindowSize() const
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	return glm::vec2(width, height);
}

glm::vec2 Core::Window::GetFramebufferSize() const
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	return glm::vec2(width, height);
}

glm::vec2 Core::Window::GetPosition() const
{
	int x, y;
	glfwGetWindowPos(window, &x, &y);

	return glm::vec2(x, y);
}

bool Core::Window::GetMonitorSync() const
{
	return data.vSync;
}

void Core::Window::SetCenter()
{
	int windowX, windowY;
	glfwGetWindowPos(window, &windowX, &windowY);

	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	windowWidth *= 0.5;
	windowHeight *= 0.5;

	windowX += windowWidth;
	windowY += windowHeight;

	int monitorsLength;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorsLength);
	if (monitors == nullptr)
		return;

	GLFWmonitor* monitor = nullptr;
	int monitorX, monitorY, monitorWidth, monitorHeight;

	for (int i = 0; i < monitorsLength; i++)
	{
		int monitorsX, monitorsY;
		glfwGetMonitorPos(monitors[i], &monitorsX, &monitorsY);

		int monitorsWidth, monitorsHeight;
		GLFWvidmode* monitorVideoMode = (GLFWvidmode*)glfwGetVideoMode(monitors[i]);
		if (monitorVideoMode == nullptr)
			continue;
		else
		{
			monitorsWidth = monitorVideoMode->width;
			monitorsHeight = monitorVideoMode->height;
		}

		if ((windowX > monitorsX && windowX < (monitorsX + monitorsWidth)) && (windowY > monitorsY && windowY < (monitorsY + monitorsHeight)))
		{
			monitor = monitors[i];

			monitorX = monitorsX;
			monitorY = monitorsY;

			monitorWidth = monitorsWidth;
			monitorHeight = monitorsHeight;
		}
	}

	if (monitor != nullptr)
		glfwSetWindowPos(window, monitorX + (monitorWidth * 0.5) - windowWidth, monitorY + (monitorHeight * 0.5) - windowHeight);
}

void Core::Window::Fullscreen()
{
	if (glfwGetWindowMonitor(window) == nullptr)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videoMode = (GLFWvidmode*)glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);

		glfwSwapBuffers(window);
	}
	else
	{
		glfwSetWindowMonitor(window, nullptr, 0, 0, data.width, data.height, 0);
		Window::SetCenter();

		glfwSwapBuffers(window);
	}
}
