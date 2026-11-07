#pragma once

#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include <GLFW/glfw3.h>

#include "App.h"

#include "../Object/Camera/Camera.h"
#include "../Object/Selection/Selection.h"
#include "../Object/Gizmo/Gizmo.h"

namespace Engine
{
	class Scene
	{
	public:
		glm::vec3 skyColor = glm::vec3(0.529f, 0.808f, 0.922f);
		std::string name;

	protected:
		Core::App& app;

		Selection selection;
		Gizmo gizmo;

	public:
		Scene(Core::App& app, const std::string& name);
		virtual ~Scene() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;

		virtual Camera GetCamera() const = 0;
		virtual GLuint GetViewportTexture() const = 0;
		virtual glm::vec2 GetViewportSize() const = 0;
	};
}

#endif
