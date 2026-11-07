#pragma once

#ifndef ENGINE_SAMPLE_H
#define ENGINE_SAMPLE_H

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
#include "../Grid/Grid.h"
#include "../Object/Camera/Camera.h"
#include "../Object/Mesh/Mesh.h"
#include "../Object/Mesh/Cube.h"
#include "../Object/Mesh/Sphere.h"
#include "../Object/Mesh/Pyramid.h"
#include "../Object/Mesh/Plane.h"
#include "../Object/Mesh/Quad.h"
#include "../Object/Mesh/Triangle.h"
#include "../Object/Model/Model.h"
#include "../Object/Light/Light.h"
#include "../Object/Selection/Selection.h"
#include "../Object/Gizmo/Gizmo.h"

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

		std::vector<std::unique_ptr<Mesh>> meshes;
		std::vector<std::unique_ptr<Light>> lights;

	public:
		Sample(Core::App& app);
		virtual ~Sample() = default;

		void Render() override;
		void Update() override;

		Camera GetCamera() const override;
		GLuint GetViewportTexture() const override;
		glm::vec2 GetViewportSize() const override;
	};
}

#endif
