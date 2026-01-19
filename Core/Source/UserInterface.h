#pragma once

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <GLFW/glfw3.h>

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
