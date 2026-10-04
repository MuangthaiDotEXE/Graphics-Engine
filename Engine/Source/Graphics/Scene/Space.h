#pragma once

#ifndef ENGINE_SPACE_H
#define ENGINE_SPACE_H

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
#include "../Object/Camera/Camera.h"
#include "../Object/Mesh/Mesh.h"
#include "../Object/Mesh/Sphere.h"
#include "../Object/Light/Light.h"

namespace Engine
{
	class Space : public Scene
	{
	private:
		Core::Shader planetShader;
		Core::Shader spaceShader;
		Core::FBO fbo;

		Sky space;
		Camera camera;

		std::vector<std::unique_ptr<Mesh>> planets;
		std::vector<std::unique_ptr<Light>> stars;

	public:
		Space(Core::App& app);
		virtual ~Space() = default;

		void Render() override;
		void Update() override;

		Camera GetCamera() const override;
		GLuint GetViewportTexture() const override;
		glm::vec2 GetViewportSize() const override;
	};
}

#endif
