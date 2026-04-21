#pragma once

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <cstdio>
#include <print>
#include <string>
#include <memory>
#include <array>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Window/Window.h"

namespace Core
{
	class UserInterface
	{
	private:
		std::string title, version, graphicsAPI;
		Window* window;

		bool wireframeMode = false;

	public:
		UserInterface(Window* window, const std::string& title, const std::string& version, const std::string& graphicsAPI);
		virtual ~UserInterface();

		void Render();
		void BeginFrame();
		void Update();
		void EndFrame();

		void DebugWindow();
		void DemoWindow();
	};
}

#endif
