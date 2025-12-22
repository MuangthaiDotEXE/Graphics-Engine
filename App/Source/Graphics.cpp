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
		throw std::exception("Failed to load OpenGL contexts");
	}
}

void App::Graphics::Render()
{
}

void App::Graphics::Update()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
