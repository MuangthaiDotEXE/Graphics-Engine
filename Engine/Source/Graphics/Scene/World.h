#pragma once

#ifndef WORLD_H
#define WORLD_H

#include "Graphics/Shader/FBO.h"
#include "App.h"

#include "Scene.h"
#include "../Sky/Sky.h"
#include "../Camera/Camera.h"
#include "../Grid/Grid.h"

namespace Engine
{
	class World : public Scene
	{
	private:
		Core::FBO fbo;

		Grid grid;
		Sky sky;

	public:
		Camera camera;

	public:
		World(Core::App& app);
		virtual ~World() = default;

		void Render() override;
		void Update() override;

		Camera GetCamera() const override;
		GLuint GetViewportTexture() const override;
		glm::vec2 GetViewportSize() const override;
	};
}

#endif
