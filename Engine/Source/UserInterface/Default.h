#pragma once

#ifndef ENGINE_USERINTERFACE_DEFAULT_H
#define ENGINE_USERINTERFACE_DEFAULT_H

#include <print>
#include <format>
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

#include "Window/Window.h"
#include "UserInterface/UserInterface.h"

namespace Engine::UserInterface
{
	class Default : public Core::UserInterface::UserInterface
	{
	protected:
		std::string title, graphicsAPI;
		std::string version;
		glm::vec3 skyColor, defaultSkyColor;

		bool vSync;
		glm::vec3 cameraPosition;

	public:
		Default(Core::Window* window, 
			const std::string& title, 
			const std::string& version,
			const std::string& graphicsAPI, 
			const glm::vec3& skyColor
		);
		virtual ~Default();

		void Render() override;
		void Update() override;

		void SetCameraPosition(glm::vec3 position);

	private:
		void DefaultWindow();
		void ViewportWindow(GLuint textureID, glm::vec2 size);

		void DockSpace();
		void DeveloperWindow();
	};
}

#endif
