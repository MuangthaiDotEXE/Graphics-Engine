#include "App.h"

#ifdef _WIN32
std::string operatingSystem = "Windows";
#elifdef __APPLE__ || __MACH__
std::string operatingSystem = "Macintosh";
#elifdef __linux__
std::string operatingSystem = "Linux";
#elifdef __FREEBSD__
std::string operatingSystem = "FreeBSD";
#elifdef __unix__ || __unix
std::string operatingSystem = "Unix";
#else
std::string operatingSystem = "Unknown";
#endif

static Core::App* app = nullptr;

Core::App::App(const AppData& appData = AppData())
	: appData(appData), running(true)
{
	app = this;

	if (this->appData.windowData.title.empty() || (!this->appData.name.empty() || !this->appData.version.empty()))
	{
		this->appData.windowData.title = this->appData.name + " " + version;
		title = this->appData.name;
	}

	// version system: major, minor, patch
	if (!appData.version.empty())
	{
		version = std::format("v{}.{}.{}{} build {}", appData.version[0], appData.version[1], appData.version[2], appData.subVersion, appData.buildNumber);
	}

	window = std::make_unique<Window>(this->appData.windowData, appData.graphicsAPI);

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

	std::print(stdout, "[Info] {} {}\n", title, version);
	std::print(stdout, "[Info] Operating system: {}\n", operatingSystem);
	std::print(stdout, "[Info] Graphics API: {} API\n", api);
	if (api == "Vulkan") 
		std::print(stdout, "\033[1;33m[Warn] Vulkan graphics API is currently unstable (Expect crashes). Please avoid using it if possible (Vulkan graphics API)\033[0m\n");
#ifdef NDEBUG
	std::print(stdout, "[Debug] Build: Release\n");
#else
	std::print(stdout, "[Debug] Build: Debug\n");
#endif

	std::println(stdout, "");
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

	OpenGL openGL;
	openGL.ViewportResize(window->GetWindow());
}

Core::App& Core::App::GetApplication()
{
	assert(app);
	return *app;
}

void Core::App::Quit()
{
	window->Quit();
}
