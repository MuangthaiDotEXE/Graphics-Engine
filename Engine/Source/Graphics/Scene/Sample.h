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
#include "../Sky/Sky.h"
#include "../Camera/Camera.h"
#include "../Grid/Grid.h"
#include "../Mesh/Mesh.h"
#include "../Mesh/Cube.h"
#include "../Mesh/Sphere.h"
#include "../Mesh/Pyramid.h"
#include "../Mesh/Plane.h"
#include "../Mesh/Quad.h"
#include "../Mesh/Triangle.h"
#include "../Model/Model.h"
#include "../Light/Light.h"

namespace Engine
{
	class Sample : public Scene
	{
	private:
		Core::Shader meshShader;
		Core::Shader skyShader;
		Core::FBO fbo;

		Sky sky;
		Camera camera;
		Grid grid;

		std::vector<std::unique_ptr<Mesh>> objects;
		std::vector<std::unique_ptr<Light>> lights;

	public:
		Sample(Core::App& app);
		virtual ~Sample();

		void Render() override;
		void Update() override;

		Camera GetCamera() const override;
		GLuint GetViewportTexture() const override;
		glm::vec2 GetViewportSize() const override;
	};
}

#endif
