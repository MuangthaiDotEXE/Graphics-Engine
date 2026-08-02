#pragma once

#ifndef SAMPLE_H
#define SAMPLE_H

#include <array>
#include <vector>
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include "Graphics/Shader/FBO.h"
#include "App.h"

#include "Scene.h"
#include "../Grid/Grid.h"
#include "../Mesh/Mesh.h"
#include "../Mesh/Cube.h"
#include "../Mesh/Sphere.h"
#include "../Mesh/Pyramid.h"
#include "../Mesh/Plane.h"
#include "../Mesh/Quad.h"
#include "../Mesh/Triangle.h"
#include "../Light/Light.h"
#include "../Camera/Camera.h"

namespace Engine
{
	class Sample : public Scene
	{
	private:
		Core::Shader meshShader;
		Core::FBO fbo;

		std::vector<std::unique_ptr<Mesh>> objects;
		std::vector<std::unique_ptr<Light>> lights;

		float nearPlane = 0.001f, farPlane = 1000.0f;

	public:
		Grid grid;
		Camera camera;

		glm::vec3 skyColor = glm::vec3(0.529f, 0.808f, 0.922f);

	public:
		Sample(Core::App& app);
		virtual ~Sample();

		void Render() override;
		void Update() override;

		GLuint GetViewportTexture() const;
		glm::vec2 GetViewportSize() const;
	};
}

#endif
