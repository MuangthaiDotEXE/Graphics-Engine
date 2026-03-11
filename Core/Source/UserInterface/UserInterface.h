#pragma once

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

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
		GLFWwindow* window;

	public:
		UserInterface(GLFWwindow* window);
		virtual ~UserInterface();

		void Render();
		void Update();
	};
}

#endif
