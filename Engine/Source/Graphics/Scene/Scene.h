#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <GLFW/glfw3.h>

#include "App.h"

namespace Engine
{
	class Scene
	{
	public:
		glm::vec3 skyColor = glm::vec3(0.529f, 0.808f, 0.922f);

	protected:
		Core::App& app;

	public:
		Scene(Core::App& app);
		virtual ~Scene() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;

		virtual GLuint GetViewportTexture() const = 0;
		virtual glm::vec2 GetViewportSize() const = 0;
	};
}

#endif
