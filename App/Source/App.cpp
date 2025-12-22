#include "App.h"

static App::App* app = nullptr;

App::App::App(const AppData& appData = AppData())
	: data(appData), running(true)
{
	app = this;

	if (data.windowData.title.empty() || !data.name.empty())
		data.windowData.title = data.name;

	window = std::make_unique<Window>(data.windowData);
	graphics.LoadContexts();
}

App::App::~App()
{
	running = false;

	window->~Window();

	app = nullptr;
	free(app);
}

void App::App::Render()
{
	window->Render();
	graphics.Render();
}

void App::App::Update()
{
	while (!window->ShouldClose() && running == true)
	{
		window->Update();
		graphics.Update();
	}
}

App::App& App::App::GetApplication()
{
	assert(app);

	return *app;
}
