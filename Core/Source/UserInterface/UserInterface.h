#pragma once

#ifndef CORE_USERINTERFACE_H
#define CORE_USERINTERFACE_H

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

namespace Core::UserInterface
{
	class UserInterface
	{
	public:
		Window* window;
		std::string name;

	public:
		UserInterface(Window* window, const std::string& name);
		virtual ~UserInterface() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;
	};
}

#endif
