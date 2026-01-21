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

namespace Core
{
	enum class GraphicsAPI
	{
		OPENGL,
		VULKAN
	};

	class Graphics
	{
	public:
		Graphics();
		virtual ~Graphics() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;
		virtual void ViewportResize(GLFWwindow* window) = 0;
	};
}

#endif
