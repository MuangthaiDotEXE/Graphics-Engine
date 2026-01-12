#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <cstdint>
#include <string>
#include <stdexcept>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace App
{
	struct WindowData
	{
		uint32_t width = 640u, height = 480u;
		std::string title = "App";
		bool vSync = true;
		bool resizable = true;
		bool decorated = true;
	};

	class Window
	{
	private:
		GLFWwindow* window;
		WindowData data;

	public:
		Window(const WindowData& windowData);
		virtual ~Window();

		void Render();
		void Update();

		[[nodiscard]] bool ShouldClose() const;
		GLFWwindow* GetWindow() const;
		glm::vec2 GetSize() const;
		void SetCenter();
	};
}

#endif
