#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdexcept>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

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
