#pragma once

#ifndef WORLD_H
#define WORLD_H

#include "App.h"

#include "Scene.h"
#include "../Grid/Grid.h"
#include "../Camera/Camera.h"
#include "../Sky/Sky.h"

namespace Engine
{
	class World : public Scene
	{
	private:
		Grid grid;
		Sky sky;

	public:
		Camera camera;

	public:
		World(Core::App& app);
		virtual ~World() = default;

		void Render() override;
		void Update() override;

		GLuint GetViewportTexture() const override;
		glm::vec2 GetViewportSize() const override;
	};
}

#endif
