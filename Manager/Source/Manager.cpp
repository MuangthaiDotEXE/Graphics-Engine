#include "Manager.h"

Manager::Manager::Manager(const Core::AppData& appData)
	: app(appData)
{
}

Manager::Manager::~Manager()
{
}

void Manager::Manager::Render()
{
	app.Render();
}

void Manager::Manager::Update()
{
	while (!app.window->ShouldClose())
	{
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

		app.Update();
	}
}
