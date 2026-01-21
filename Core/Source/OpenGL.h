#pragma once

#ifndef OPENGL_H
#define OPENGL_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Graphics.h"

namespace Core
{
	class OpenGL final : public Graphics
	{
	private:
		int version;

	public:
		OpenGL();
		virtual ~OpenGL() = default;

		void Render() override;
		void Update() override;
		void ViewportResize(GLFWwindow* window) override;
	};
}

#endif
