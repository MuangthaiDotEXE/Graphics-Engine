#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <print>
#include <memory>
#include <stdexcept>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Window.h"

namespace App
{
	class Graphics
	{
	private:
		int version;

	public:
		Graphics();
		virtual ~Graphics();

		void Render();
		void Update();
		void LoadContexts();
		void ViewportResize(GLFWwindow* window);
	};
}

#endif
