#include "App.h"

#ifdef _WIN32
std::string operatingSystem = "Windows";
#elif defined(__APPLE__) || defined(__MACH__)
std::string operatingSystem = "Macintosh";
#elifdef __linux__
std::string operatingSystem = "Linux";
#elifdef __FREEBSD__
std::string operatingSystem = "FreeBSD";
#elif defined(__unix__) || defined(__unix)
std::string operatingSystem = "Unix";
#else
std::string operatingSystem = "Unknown";
#endif

static Core::App* app = nullptr;

Core::App::App(const AppData& appData)
	: appData(appData), running(true)
{
	app = this;

	if (!this->appData.name.empty() || !this->appData.version.empty())
	{
		this->appData.windowData.title = this->appData.name + " " + version;
		title = this->appData.name;
	}

	// version system: major, minor, patch (Semantic versioning)
	if (!appData.version.empty())
	{
		version = std::format("v{}.{}.{}{} {} Build {}", appData.version[0], appData.version[1], appData.version[2], appData.subVersion, GetDevelopmentStage(), appData.buildNumber);
	}

	window = std::make_unique<Window>(this->appData.windowData, appData.graphicsAPI);

	std::string api = GetGraphicsAPI();

	std::print(stdout, "[Info] {} {}\n", title, version);
	std::print(stdout, "[Info] Operating system: {}\n", operatingSystem);
	std::print(stdout, "[Info] Graphics API: {} API\n", api);
	if (api == "Vulkan") 
	{
		std::print(stdout, "\033[33m[Warn] Vulkan graphics API is currently unstable (Expect crashes). Please avoid using it if possible (Vulkan graphics API)\033[0m\n");
	}
	std::print(stdout, "[Info] Build: {}\n", GetConfigurations());

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
	graphics->ViewportResize();
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

std::string Core::App::GetConfigurations()
{
#ifdef NDEBUG
	return "Release";
#else
	return "Debug";
#endif
}

std::string Core::App::GetGraphicsAPI()
{
	switch (appData.graphicsAPI)
	{
	case GraphicsAPI::OPENGL:
#define OPENGL_API
		graphics = std::make_unique<OpenGL>(window->GetWindow());
		return "OpenGL";

		break;

	case GraphicsAPI::VULKAN:
#define VULKAN_API
		graphics = std::make_unique<Vulkan>(window->GetWindow());
		return "Vulkan";

		break;

	default:
#define OPENGL_API
		graphics = std::make_unique<OpenGL>(window->GetWindow()); // Default to OpenGL graphics API
		return "OpenGL";

		break;
	}
}

std::string Core::App::GetDevelopmentStage()
{
	switch (appData.developmentStage)
	{
	case AppData::DevelopmentStage::ALPHA: return "Alpha";
	case AppData::DevelopmentStage::BETA: return "Beta";
	case AppData::DevelopmentStage::RELEASE_CANDIDATE: return "Release candidate";
	case AppData::DevelopmentStage::RELEASE: return "Release";
	default: return "";
	}
}
