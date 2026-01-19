#include "App.h"

static Core::App* app = nullptr;

Core::App::App(const AppData& appData = AppData())
	: data(appData), running(true), ui()
{
	app = this;

	// version system: major, minor, patch
	std::string version = std::format("v{}.{}.{}", appData.version[0], appData.version[1], appData.version[2]);

	if (data.windowData.title.empty() || (!data.name.empty() || !data.version.empty()))
	{
		data.windowData.title = data.name + " " + version;
	}

	window = std::make_unique<Window>(data.windowData);
	graphics.LoadContexts();
	ui.emplace(window->GetWindow());

	running = true;
}

Core::App::~App()
{
	running = false;

	window.reset();

	app = nullptr;
	free(app);
}

void Core::App::Render()
{
	window->Render();
	graphics.Render();
	ui->Render();
}

void Core::App::Update()
{
	window->Input();
	window->Update();
	graphics.Update();
	graphics.ViewportResize(window->GetWindow());
	ui->Update();
}

Core::App& Core::App::GetApplication()
{
	assert(app);

	return *app;
}
