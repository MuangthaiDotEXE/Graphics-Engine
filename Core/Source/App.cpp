#include "App.h"

static Core::App* app = nullptr;

Core::App::App(const AppData& appData = AppData())
	: data(appData), running(true)
{
	app = this;

	if (data.windowData.title.empty() || (!data.name.empty() || !data.version.empty()))
	{
		data.windowData.title = data.name + " " + version;
		title = data.name;
	}

	// version system: major, minor, patch
	if (!appData.version.empty())
	{
		version = std::format("v{}.{}.{}{} build {}", appData.version[0], appData.version[1], appData.version[2], appData.subVersion, appData.buildNumber);
	}

	window = std::make_unique<Window>(data.windowData, appData.graphicsAPI);

	switch (appData.graphicsAPI) 
	{
	case GraphicsAPI::OPENGL:
		graphics = std::make_unique<OpenGL>();
		api = "OpenGL";

		break;

	case GraphicsAPI::VULKAN:
		graphics = std::make_unique<Vulkan>();
		api = "Vulkan";

		break;

	default:
		graphics = std::make_unique<OpenGL>(); // Default to OpenGL graphics API
		api = "OpenGL";

		break;
	}

	std::print("{} {}\n", title, version);
	std::print("Graphics API: {} API\n", api);
	if (api == "Vulkan") std::print("[Warning] Vulkan graphics API is currently unstable. Please avoid using it if possible (Vulkan graphics API)\n");
#ifdef NDEBUG
	std::print("Build: Release\n");
#else
	std::print("Build: Debug\n");
#endif

	running = true;
}

Core::App::~App()
{
	running = false;
	app = nullptr;
}

void Core::App::Render()
{
	window->Render();
	graphics->Render();
}

void Core::App::Update()
{
	window->Input();
	window->Update();
	graphics->Update();
	graphics->ViewportResize(window->GetWindow());
}

Core::App& Core::App::GetApplication()
{
	assert(app);
	return *app;
}
