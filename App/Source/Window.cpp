#include "Window.h"

App::Window::Window(const WindowData& windowData = WindowData())
	: data(windowData)
{
	glfwInit();
	if (!glfwInit())
	{
		throw std::exception("Failed to initialize window");
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
		throw std::exception("Failed to create window");
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(data.vSync);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

App::Window::~Window()
{
	if (window != nullptr || window)
		glfwDestroyWindow(window);

	glfwTerminate();
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
		throw std::exception("Unable to return window because window does not exist.");
	}

	return this->window;
}

glm::vec2 App::Window::GetSize() const
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	return glm::vec2(width, height);
}
