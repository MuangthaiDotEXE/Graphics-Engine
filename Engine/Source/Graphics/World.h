#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "App.h"

#include "Scene.h"
#include "Mesh/Mesh.h"
#include "Mesh/Cube.h"
#include "Mesh/Plane.h"
#include "Light/Light.h"
#include "Camera/Camera.h"

namespace Engine
{
	class World : public Scene
	{
	private:
		Core::Shader shader;

		std::vector<std::unique_ptr<Mesh>> objects;
		std::vector<std::unique_ptr<Light>> lights;
		Camera camera;

		float nearPlane = 0.001f, farPlane = 1000.0f;

	public:
		World(Core::App& app);
		virtual ~World();

		void Render() override;
		void Update() override;
	};
}

#endif
