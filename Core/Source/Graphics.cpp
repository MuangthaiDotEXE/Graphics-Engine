#include "Graphics.h"

Core::Graphics::Graphics()
{
}

Core::Graphics::~Graphics()
{
}

void Core::Graphics::LoadContexts()
{
	version = gladLoadGL(glfwGetProcAddress);

	if (version == 0)
	{
		throw std::exception("Failed to load OpenGL contexts (OpenGL graphics API)");
	}
}

void Core::Graphics::Render()
{
	glEnable(GL_DEPTH_TEST);
}

void Core::Graphics::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Core::Graphics::ViewportResize(GLFWwindow* window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
}
