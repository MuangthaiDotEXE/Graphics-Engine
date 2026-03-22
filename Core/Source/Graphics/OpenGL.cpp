#include "OpenGL.h"

Core::OpenGL::OpenGL()
	: version(gladLoadGL(glfwGetProcAddress))
{
	if (version == 0)
	{
		throw std::exception("Failed to load OpenGL contexts (OpenGL graphics API)\n");
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Core::OpenGL::Render()
{
}

void Core::OpenGL::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Core::OpenGL::ViewportResize(GLFWwindow* window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
}
