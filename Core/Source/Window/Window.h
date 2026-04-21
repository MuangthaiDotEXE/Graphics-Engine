#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <print>
#include <cstdio>
#include <cstdint>
#include <string>
#include <filesystem>
#include <stdexcept>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#include "../Graphics/Graphics.h"

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <dwmapi.h>
#include <winreg.h>
#include <commctrl.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "comctl32.lib")
#endif

namespace Core
{
	struct WindowData
	{
		std::string title = "App";
		std::string icon = "";
		uint32_t width = 640u, height = 480u;
		bool vSync = true;
		bool resizable = true;
		bool decorated = true;
	};

	class Window
	{
	private:
		GLFWwindow* window;
		WindowData windowData;

		GraphicsAPI graphicsAPI;

		double toggleTime = 0.0;
		const double debounceTime = 0.15;

#ifdef _WIN32
		HWND hwnd;
#endif

	public:
		Window(const WindowData& windowData, GraphicsAPI graphicsAPI);
		virtual ~Window();

		void Input();
		void Render();
		void Update();

		[[nodiscard]] bool ShouldClose() const;
		void Quit();

		GLFWwindow* GetWindow() const;
		std::string GetTitle() const;
		glm::vec2 GetWindowSize() const;
		glm::vec2 GetFramebufferSize() const;
		glm::vec2 GetPosition() const;
		bool GetMonitorSync() const;

		void SetTitle(const std::string& title);
		void SetPosition(glm::vec2 position);

	private:
		void SetCenter();
		void Fullscreen();
	};
}

#endif
