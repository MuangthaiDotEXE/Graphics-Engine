#include "Window.h"

App::Window::Window(const WindowData& windowData = WindowData())
	: data(windowData)
{
	glfwInit();
	if (!glfwInit())
	{
		throw std::exception("Failed to initialize window (GLFW windowing API)");
	}

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, data.resizable);
	glfwWindowHint(GLFW_DECORATED, data.decorated);

	window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
	if (window == nullptr || !window)
	{
		glfwTerminate();
		throw std::exception("Failed to create window (GLFW windowing API)");
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(data.vSync);

	SetCenter();

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

App::Window::~Window()
{
	if (window != nullptr || window)
		glfwDestroyWindow(window);

	glfwTerminate();
}

void App::Window::Input()
{
	// Mouse
	{
		
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

void App::Window::Render()
{
	glfwShowWindow(window);
}

void App::Window::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool App::Window::ShouldClose() const
{
	return glfwWindowShouldClose(window);
}

GLFWwindow* App::Window::GetWindow() const
{
	if (window == nullptr || !window)
	{
		throw std::exception("Unable to return window because window does not exist (GLFW windowing API)");
	}

	return this->window;
}

glm::vec2 App::Window::GetWindowSize() const
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	return glm::vec2(width, height);
}

glm::vec2 App::Window::GetFramebufferSize() const
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	return glm::vec2(width, height);
}

void App::Window::SetCenter()
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

void App::Window::Fullscreen()
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
