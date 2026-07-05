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
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
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

		glm::vec3 skyColor;

		bool vSync;

	public:
		glm::vec3 coordinate;

	public:
		UserInterface(Window* window, const std::string& title, const std::string& version, const std::string& graphicsAPI, const glm::vec3& skyColor);
		virtual ~UserInterface();

		void Render();
		void BeginFrame();
		void Update();
		void EndFrame();

		void DebugWindow();
		void ViewportWindow(GLuint textureID, glm::vec2 size);

	private:
		void DockSpace();

		void DevWindow();
	};
}

#endif
