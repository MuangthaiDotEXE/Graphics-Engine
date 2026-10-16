#pragma once

#ifndef CORE_USERINTERFACE_LAYER
#define CORE_USERINTERFACE_LAYER

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Window/Window.h"

namespace Core::UserInterface
{
	class Layer
	{
	public:
		explicit Layer(Window* window);
		Layer(const Layer&) = delete;
		~Layer();

		Layer& operator=(const Layer&) = delete;

		void Start();
		void End();
		

	};
}

#endif
