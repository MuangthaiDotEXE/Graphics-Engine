#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include <string>
#include <cmath>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Mesh.h"

namespace Engine
{
	class Sphere : public Mesh
	{
	private:
		GLsizei indexCount;

		std::optional<std::vector<std::string>> diffusePath, specularPath;

	public:
		Sphere(std::optional<std::vector<std::string>> diffuse = std::nullopt,
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		Sphere(const Core::Shader& shader, 
			std::optional<std::vector<std::string>> diffuse = std::nullopt,
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		virtual ~Sphere() = default;

		void Render() override;
		void Update() override;

	private:
		void Initialize();
	};
}

#endif
