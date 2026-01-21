#pragma once

#ifndef VULKAN_H
#define VULKAN_H

#include <GLFW/glfw3.h>

#include "Graphics.h"

namespace Core
{
	class Vulkan final : public Graphics
	{
	private:

	public:
		Vulkan();
		virtual ~Vulkan() = default;

		void Render() override;
		void Update() override;
		void ViewportResize(GLFWwindow* window) override;
	};
}

#endif
