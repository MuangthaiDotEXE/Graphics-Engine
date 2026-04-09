#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "App.h"

#include "Mesh/Mesh.h"
#include "Mesh/Cube.h"
#include "Mesh/Plane.h"
#include "Light/Light.h"
#include "Camera/Camera.h"

namespace Engine
{
	class World
	{
	private:
		Core::App& app;
		Core::Shader shader;

		std::vector<std::unique_ptr<Mesh>> object;
		std::unique_ptr<Light> light;
		Camera camera;

		float nearPlane = 0.001f, farPlane = 1000.0f;

	public:
		World(Core::App& app);
		virtual ~World();

		void Render();
		void Update();
	};
}

#endif
