#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "App.h"

#include "Mesh/Object.h"
#include "Light/Light.h"
#include "Camera/Camera.h"

namespace Engine
{
	class World
	{
	private:
		Core::App& app;

		Object mesh;
		Light light;
		Camera camera;

	public:
		World(Core::App& app);
		virtual ~World();

		void Render();
		void Update();
	};
}

#endif
