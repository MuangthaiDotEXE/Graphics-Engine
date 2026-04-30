#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GLFW/glfw3.h>

namespace Core
{
	enum class GraphicsAPI
	{
		OPENGL,
		VULKAN
	};

	class Graphics
	{
	protected:
		GLFWwindow* window;

	public:
		Graphics(GLFWwindow* window);
		virtual ~Graphics() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;
		virtual void ViewportResize() {}
	};
}

#endif
