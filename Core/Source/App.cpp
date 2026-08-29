#include "App.h"

#ifdef _WIN32
std::string operatingSystem = "Windows";
#elif defined(__APPLE__) || defined(__MACH__)
std::string operatingSystem = "Macintosh";
#elif defined(__linux__)
std::string operatingSystem = "Linux";
#elif defined(__FREEBSD__)
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

	// version system: major, minor, patch (Semantic versioning)
	if (!appData.version.empty())
	{
		version = std::format("v{}.{}.{}{} {} Build {}", appData.version[0], appData.version[1], appData.version[2], appData.subVersion, GetDevelopmentStage(), appData.buildNumber);
	}

	if (!appData.appName.empty() || !appData.version.empty())
	{
		this->appData.windowData.title = appData.appName;
		title = appData.appName;
	}

	window = std::make_unique<Window>(this->appData.windowData, appData.graphicsAPI);

	api = GetGraphicsAPI();

	std::print(stdout, "[Info] {} {}\n", title, version);
	std::print(stdout, "[Info] Operating system: {}\n", operatingSystem);
	std::print(stdout, "[Info] Graphics API: {} API\n", api);
	if (api == "Vulkan") 
	{
		std::print(stdout, "\033[33m[Warn] Vulkan graphics API is currently in an unstable state (Expect crashes). If possible, please avoid using it (System)\033[0m\n");
	}
	std::println(stdout, "[Info] Build: {}\n", GetConfigurations());
	PrintGraphicsInformation();

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

void Core::App::PrintGraphicsInformation()
{
	std::print(stdout, R"([Info] Graphics device information:
	> Vendor:           {}
	> Renderer:         {}
	> Version:          {}
	> Shading language: {}
)",
	graphicsVendor, graphicsRenderer, graphicsVersion, graphicsShadingLanguage);
}

void Core::App::Quit()
{
	window->Close();
}

std::string Core::App::GetConfigurations() const
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
		graphics = std::make_unique<OpenGL>(window->GetWindow());

		graphicsVendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		graphicsRenderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		graphicsVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		graphicsShadingLanguage = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

		return "OpenGL";

		break;

	case GraphicsAPI::VULKAN:
		graphics = std::make_unique<Vulkan>(window->GetWindow(), appData.appName, appData.engineName);

		graphicsVendor = "NOT_AVAILABLE";
		graphicsRenderer = "NOT_AVAILABLE";
		graphicsVersion = "NOT_AVAILABLE";
		graphicsShadingLanguage = "NOT_AVAILABLE";

		return "Vulkan";

		break;

	default:
		graphics = std::make_unique<OpenGL>(window->GetWindow()); // Default to OpenGL graphics API

		graphicsVendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		graphicsRenderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		graphicsVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		graphicsShadingLanguage = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

		return "OpenGL";

		break;
	}
}

std::string Core::App::GetTitle() const
{
	return title;
}

std::array<unsigned int, 3> Core::App::GetVersion() const
{
	return appData.version;
}

std::string Core::App::GetDevelopmentStage() const
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

Core::App& Core::App::GetApplication()
{
	assert(app);
	return *app;
}
