#include "OpenGL.h"

Core::OpenGL::OpenGL()
	: version(gladLoadGL(glfwGetProcAddress))
{
	if (version == 0)
	{
		throw std::exception("Failed to load OpenGL contexts (OpenGL graphics API)\n");
	}
}

void Core::OpenGL::Render()
{
	glEnable(GL_DEPTH_TEST);
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
