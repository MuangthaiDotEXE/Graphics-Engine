#include "Window.h"

namespace
{
	const std::filesystem::path windowStatePath = std::filesystem::path("Config") / "Window.state";

	std::string TrimWhiteSpace(const std::string& value)
	{
		const auto first = value.find_first_not_of(" \t\r\n");
		if (first == std::string::npos)
		{
			return {};
		}

		const auto last = value.find_last_not_of(" \t\r\n");
		return value.substr(first, last - first + 1);
	}

	bool ParseInteger(const std::string& value, int& result)
	{
		if (value.empty())
		{
			return false;
		}

		int parsedValue{};
		const auto [pointer, error] = std::from_chars(value.data(), value.data() + value.size(), parsedValue);
		if (error != std::errc{} || pointer != value.data() + value.size())
		{
			return false;
		}

		result = parsedValue;
		return true;
	}

	bool ParseBoolean(const std::string& value, bool& result)
	{
		if (value == "true" || value == "1")
		{
			result = true;
			return true;
		}
		else if (value == "false" || value == "0")
		{
			result = false;
			return true;
		}

		return false;
	}

#ifdef _WIN32
	static void ApplyTitleBarTheme(HWND hwnd)
	{
		bool systemDarkMode = false;
		HKEY hKey;
		if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
		{
			DWORD value = 0;
			DWORD size = sizeof(value);

			if (RegQueryValueExW(hKey, L"AppsUseLightTheme", nullptr, nullptr, reinterpret_cast<LPBYTE>(&value), &size) == ERROR_SUCCESS)
			{
				systemDarkMode = (value == 0);
			}

			RegCloseKey(hKey);
		}

		BOOL useDarkMode = systemDarkMode ? TRUE : FALSE;
		DwmSetWindowAttribute(hwnd, 20, &useDarkMode, sizeof(useDarkMode));

#if 0	// for Windows 11 only (For custom titlebar color), currently disabled
		COLORREF titleBarColor = systemDarkMode ? RGB(16, 16, 16) : RGB(240, 240, 240);
		DwmSetWindowAttribute(hwnd, 35, &titleBarColor, sizeof(titleBarColor));
#endif

		SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE);
	}

	static LRESULT CALLBACK ThemeSubclassProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		if (msg == WM_SETTINGCHANGE && lParam != 0)
		{
			if (wcscmp(reinterpret_cast<LPCWSTR>(lParam), L"ImmersiveColorSet") == 0)
			{
				ApplyTitleBarTheme(hwnd);
			}
		}

		return DefSubclassProc(hwnd, msg, wParam, lParam);
	}
#endif

	static void ErrorCallback(int error, const char* description)
	{
		Core::Log::Error("Window", std::format("GLFW error {}: {}", error, description));
	}
}

Core::Window::Window(const WindowData& windowData, GraphicsAPI graphicsAPI)
	: windowData(windowData), graphicsAPI(graphicsAPI), width(windowData.width), height(windowData.height), fullscreenMode(windowData.fullscreen)
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		Log::Critical("Window", "Failed to initialize window library");
		throw std::runtime_error("Failed to initialize window (GLFW windowing API)\n");
	}

	if (graphicsAPI == GraphicsAPI::OPENGL)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
	}
	else if (graphicsAPI == GraphicsAPI::VULKAN)
	{
		if (!glfwVulkanSupported())
		{
			glfwTerminate();
			Log::Critical("GRAPHICS", "Vulkan graphics API is not supported");
			throw std::runtime_error("Vulkan graphics API is not supported (GLFW windowing API)\n");
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	glfwWindowHint(GLFW_RESIZABLE, windowData.resizable);
	glfwWindowHint(GLFW_DECORATED, windowData.decorated);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	window = glfwCreateWindow(windowData.width, windowData.height, windowData.title.c_str(), nullptr, nullptr);
	if (window == nullptr || !window)
	{
		glfwTerminate();
		Log::Critical("Window", "Failed to create window");
		throw std::runtime_error("Failed to create window (GLFW windowing API)\n");
	}

#ifdef _WIN32
	hwnd = glfwGetWin32Window(window);

	ApplyTitleBarTheme(hwnd);
	SetWindowSubclass(hwnd, ThemeSubclassProcess, 1, 0);
#endif

	if (graphicsAPI == GraphicsAPI::OPENGL)
	{
		glfwMakeContextCurrent(window);

		glfwSwapInterval(windowData.vSync);
	}

	if (windowData.icon.has_value() && std::filesystem::exists(*windowData.icon))
	{
		GLFWimage icon[1];
		int width, height, channels;

		unsigned char* image = stbi_load((*windowData.icon).c_str(), &width, &height, &channels, STBI_rgb_alpha);

		if (image)
		{
			icon[0].width = width;
			icon[0].height = height;
			icon[0].pixels = image;

			glfwSetWindowIcon(window, 1, icon);

			stbi_image_free(image);
		}
	}
	else if (windowData.icon.has_value() && !std::filesystem::exists(*windowData.icon))
	{
		Log::Warn("Window", std::format("Failed to load icon with path: '{}'. Application will use operating system's default icon instead", *windowData.icon));
	}

	restoredWidth = windowData.width;
	restoredHeight = windowData.height;
	restoredX = 0;
	restoredY = 0;

	WindowState savedState;
	if (LoadState(savedState))
	{
		glfwSetWindowSize(window, savedState.width, savedState.height);
		glfwSetWindowPos(window, savedState.x, savedState.y);

		if (savedState.fullscreen)
		{
			fullscreenMode = true;
			Fullscreen();
		}
		else if (savedState.maximized)
		{
			glfwMaximizeWindow(window);
		}

		restoredWidth = savedState.width;
		restoredHeight = savedState.height;
		restoredX = savedState.x;
		restoredY = savedState.y;
	}
	else
	{
		SetCenter();
	}

	if (windowData.fullscreen)
	{
		Fullscreen();
	}

	if (glfwRawMouseMotionSupported())
	{
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
}

Core::Window::~Window()
{
	SaveState();

#ifdef _WIN32
	if (hwnd != nullptr)
	{
		RemoveWindowSubclass(hwnd, ThemeSubclassProcess, 1);
	}
#endif

	if (window != nullptr)
	{
		glfwDestroyWindow(window);
	}

	glfwTerminate();
}

void Core::Window::Input()
{
	// Keyboard
	{
		double currentTime = glfwGetTime();

		if (currentTime - toggleTime > debounceTime)
		{
			if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS)
			{
				fullscreenMode = !fullscreenMode;

				Fullscreen();
				toggleTime = currentTime;
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(window, true);
				toggleTime = currentTime;
			}
		}
	}
}

void Core::Window::Render()
{
	glfwShowWindow(window);
}

void Core::Window::Update()
{
	if (!fullscreenMode && !glfwGetWindowAttrib(window, GLFW_MAXIMIZED))
	{
		glfwGetWindowSize(window, &restoredWidth, &restoredHeight);
		glfwGetWindowPos(window, &restoredX, &restoredY);
	}

	if (graphicsAPI == GraphicsAPI::OPENGL)
	{
		glfwSwapBuffers(window);
	}

	glfwPollEvents();
}

bool Core::Window::ShouldClose() const
{
	return glfwWindowShouldClose(window);
}

void Core::Window::Close()
{
	glfwSetWindowShouldClose(window, true);
}

GLFWwindow* Core::Window::GetWindow() const
{
	if (window == nullptr || !window)
	{
		Log::Critical("Window", "Failed to return window because window does not exist");
		throw std::runtime_error("Failed to return window because window does not exist (GLFW windowing API)");
	}

	return window;
}

std::string Core::Window::GetTitle() const
{
	return windowData.title;
}

glm::vec2 Core::Window::GetWindowSize() const
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	return glm::vec2(width, height);
}

glm::vec2 Core::Window::GetFramebufferSize() const
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	return glm::vec2(width, height);
}

glm::vec2 Core::Window::GetPosition() const
{
	int x, y;
	glfwGetWindowPos(window, &x, &y);

	return glm::vec2(x, y);
}

bool Core::Window::GetMonitorSync() const
{
	return windowData.vSync;
}

bool Core::Window::GetFullscreenMode() const
{
	return fullscreenMode;
}

void Core::Window::SetTitle(const std::string& title)
{
	windowData.title = title;
	glfwSetWindowTitle(window, title.c_str());
}

void Core::Window::SetIcon(const std::string& path)
{
	if (!path.empty() && std::filesystem::exists(path))
	{
		GLFWimage icon[1];
		int width, height, channels;

		unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

		if (image)
		{
			icon[0].width = width;
			icon[0].height = height;
			icon[0].pixels = image;

			glfwSetWindowIcon(window, 1, icon);

			stbi_image_free(image);
		}
	}
	else if (!path.empty() && !std::filesystem::exists(path))
	{
		Log::Warn("Window", std::format("Failed to load icon with path: '{}'", path));
	}
}

void Core::Window::SetSize(glm::vec2 size)
{
	glfwSetWindowSize(window, size.x, size.y);
}

void Core::Window::SetSize(float width, float height)
{
	glfwSetWindowSize(window, width, height);
}

void Core::Window::SetPosition(glm::vec2 position)
{
	glfwSetWindowPos(window, position.x, position.y);
}

void Core::Window::SetPosition(float x, float y)
{
	glfwSetWindowPos(window, x, y);
}

void Core::Window::SetCenter()
{
	int windowX, windowY;
	glfwGetWindowPos(window, &windowX, &windowY);

	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	windowWidth *= 0.5;
	windowHeight *= 0.5;

	windowX += windowWidth;
	windowY += windowHeight;

	int monitorsLength;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorsLength);
	if (monitors == nullptr)
		return;

	GLFWmonitor* monitor = nullptr;
	int monitorX, monitorY, monitorWidth, monitorHeight;

	for (int i = 0; i < monitorsLength; i++)
	{
		int monitorsX, monitorsY;
		glfwGetMonitorPos(monitors[i], &monitorsX, &monitorsY);

		int monitorsWidth, monitorsHeight;
		GLFWvidmode* monitorVideoMode = (GLFWvidmode*)glfwGetVideoMode(monitors[i]);
		if (monitorVideoMode == nullptr)
			continue;
		else
		{
			monitorsWidth = monitorVideoMode->width;
			monitorsHeight = monitorVideoMode->height;
		}

		if ((windowX > monitorsX && windowX < (monitorsX + monitorsWidth)) && (windowY > monitorsY && windowY < (monitorsY + monitorsHeight)))
		{
			monitor = monitors[i];

			monitorX = monitorsX;
			monitorY = monitorsY;

			monitorWidth = monitorsWidth;
			monitorHeight = monitorsHeight;
		}
	}

	if (monitor != nullptr)
		glfwSetWindowPos(window, monitorX + (monitorWidth * 0.5) - windowWidth, monitorY + (monitorHeight * 0.5) - windowHeight);
}

void Core::Window::Fullscreen()
{
	if (fullscreenMode)
	{
		glfwGetWindowPos(window, &x, &y);
		glfwGetWindowSize(window, &width, &height);
	}

	if (glfwGetWindowMonitor(window) == nullptr && fullscreenMode)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videoMode = (GLFWvidmode*)glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
	}
	else
	{
		glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, 0);
		glfwSetWindowSize(window, width, height);
		glfwSetWindowPos(window, x, y);
	}
}

void Core::Window::SaveState()
{
	if (fullscreenMode)
	{
		//return;
	}

	WindowState windowState{};
	windowState.fullscreen = fullscreenMode;
	windowState.maximized = static_cast<bool>(glfwGetWindowAttrib(window, GLFW_MAXIMIZED));

	windowState.width = restoredWidth;
	windowState.height = restoredHeight;
	windowState.x = restoredX;
	windowState.y = restoredY;

	std::error_code error;
	std::filesystem::create_directories(windowStatePath.parent_path(), error);
	if (error)
	{
		Log::Error("Window", std::format("Failed to create configuration directory: {}", error.message()));
		return;
	}

	std::ofstream file(windowStatePath, std::ios::out | std::ios::trunc);
	if (!file)
	{
		Log::Error("Window", std::format("Failed to open window state file: '{}'", windowStatePath.generic_string()));
		return;
	}

	file << "# Window state configurations\n\n"
		<< "width=" << windowState.width << "\n"
		<< "height=" << windowState.height << "\n"
		<< "x=" << windowState.x << "\n"
		<< "y=" << windowState.y << "\n"
		<< "maximized=" << (windowState.maximized ? "true" : "false") << "\n"
		<< "fullscreen=" << (windowState.fullscreen ? "true" : "false") << "\n";

	file.flush();

	if (!file)
	{
		Log::Error("Window", std::format("Failed to write window state file: '{}'", windowStatePath.generic_string()));
		return;
	}

#ifndef NDEBUG
	Log::Info("Window", std::format("Save window state setting to: '{}'", std::filesystem::absolute(windowStatePath).generic_string()));
#endif
}

bool Core::Window::LoadState(WindowState& windowState)
{
	std::ifstream file(windowStatePath);
	if (!file)
	{
		return false;
	}

	WindowState loadedWindowState{};

	bool hasWidth = false;
	bool hasHeight = false;
	bool hasX = false;
	bool hasY = false;
	bool hasMaximized = false;
	bool hasFullscreen = false;

	auto WarnInvalid = [&](const std::string& reason) -> void
		{
			Log::Warn("Window", std::format("Invalid window state file: '{}': {}", windowStatePath.generic_string(), reason));
		};

	auto ParseIntegerField = [&](const std::string& key, const std::string& value, int& destination, bool& found) -> bool
		{
			if (!ParseInteger(value, destination))
			{
				WarnInvalid(std::format("invalid integer value for '{}'", key));
				return false;
			}

			found = true;
			return true;
		};

	auto ParseBooleanField = [&](const std::string& key, const std::string& value, bool& destination, bool& found) -> bool
		{
			if (!ParseBoolean(value, destination))
			{
				WarnInvalid(std::format("invalid boolean value for '{}'", key));
				return false;
			}

			found = true;
			return true;
		};

	std::string line;
	size_t lineNumber = 0;

	while (std::getline(file, line))
	{
		++lineNumber;
		line = TrimWhiteSpace(line);

		if (line.empty() || line[0] == '#' || line[0] == ';')
		{
			continue;
		}

		const auto separator = line.find("=");

		if (separator == std::string::npos)
		{
			WarnInvalid(std::format("line {} is missing '='", lineNumber));
			return false;
		}

		const std::string key = TrimWhiteSpace(line.substr(0, separator));
		const std::string value = TrimWhiteSpace(line.substr(separator + 1));

		if (key == "width")
		{
			if (!ParseIntegerField(key, value, loadedWindowState.width, hasWidth))
			{
				return false;
			}
		}
		else if (key == "height")
		{
			if (!ParseIntegerField(key, value, loadedWindowState.height, hasHeight))
			{
				return false;
			}
		}
		else if (key == "x")
		{
			if (!ParseIntegerField(key, value, loadedWindowState.x, hasX))
			{
				return false;
			}
		}
		else if (key == "y")
		{
			if (!ParseIntegerField(key, value, loadedWindowState.y, hasY))
			{
				return false;
			}
		}
		else if (key == "maximized")
		{
			if (!ParseBooleanField(key, value, loadedWindowState.maximized, hasMaximized))
			{
				return false;
			}
		}
		else if (key == "fullscreen")
		{
			if (!ParseBooleanField(key, value, loadedWindowState.fullscreen, hasFullscreen))
			{
				return false;
			}
		}
	}

	if (file.bad())
	{
		WarnInvalid("an input/output error occurred while reading the file");
		return false;
	}

	if (!hasWidth || !hasHeight || !hasX || !hasY || !hasMaximized || !hasFullscreen)
	{
		WarnInvalid("one or more required settings are missing");
		return false;
	}

	if (loadedWindowState.width <= 0 || loadedWindowState.height <= 0)
	{
		WarnInvalid("window size (width and height) must be greater than zero");
		return false;
	}

	windowState = loadedWindowState;
	return true;
}

void Core::Window::ResetState()
{
	std::error_code error;

	if (!std::filesystem::remove(windowStatePath, error) && error)
	{
		Log::Warn("Window", std::format("Faile to remove window state file: {}", error.message()));
	}

	if (fullscreenMode)
	{
		fullscreenMode = false;
		Fullscreen();
	}

	glfwRestoreWindow(window);

	glfwSetWindowSize(window, windowData.width, windowData.height);
	SetCenter();

	restoredWidth = windowData.width;
	restoredHeight = windowData.height;
	glfwGetWindowPos(window, &restoredX, &restoredY);

#ifndef NDEBUG
	Log::Debug("Window", "Reset window state to default value");
#endif
}
