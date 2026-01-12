#include "Graphics.h"

App::Graphics::Graphics()
{
}

App::Graphics::~Graphics()
{
}

void App::Graphics::LoadContexts()
{
	version = gladLoadGL(glfwGetProcAddress);

	if (version == 0)
	{
		throw std::exception("Failed to load OpenGL contexts (OpenGL graphics API)");
	}
}

void App::Graphics::Render()
{
	glEnable(GL_DEPTH_TEST);
}

void App::Graphics::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void App::Graphics::ViewportResize(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glViewport(0, 0, width, height);
}
