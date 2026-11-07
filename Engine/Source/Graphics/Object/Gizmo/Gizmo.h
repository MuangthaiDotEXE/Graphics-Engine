#pragma once

#ifndef ENGINE_GIZMO_H
#define ENGINE_GIZMO_H

#include <cmath>
#include <algorithm>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <ImGuizmo.h>

#include "../Mesh/Mesh.h"
#include "../Camera/Camera.h"

namespace Engine
{
	class Gizmo
	{
	public:
		enum struct Mode
		{
			NONE,
			TRANSLATE,
			ROTATE,
			SCALE,
			TRANSFORM
		};

		enum struct Space
		{
			GLOBAL,
			LOCAL
		};

		Mode mode = Mode::TRANSLATE;
		Space space = Space::GLOBAL;

		float snapTranslate = 1.0f;
		float snapRotate = 15.0f;
		float snapScale = 0.1f;

		float size = 0.15f;

	private:
		bool interacting = false;

	public:
		Gizmo() = default;
		virtual ~Gizmo() = default;

		void Draw(Mesh* mesh, Camera& camera, const glm::vec2& viewportPosition, const glm::vec2& viewportSize);

		bool IsInteracting() const;

	private:
		void Keybinds();
	};
}

#endif
