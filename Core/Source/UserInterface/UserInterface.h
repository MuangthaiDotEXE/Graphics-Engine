#pragma once

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <cstdio>
#include <print>
#include <string>
#include <array>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Core
{
	class UserInterface
	{
	private:
		std::string title, version, graphicsAPI;
		GLFWwindow* window;

	public:
		UserInterface(std::string title, std::string version, std::string graphicsAPI, GLFWwindow* window);
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
