#pragma once

#ifndef PLANE_H
#define PLANE_H

#include <string>
#include <array>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "Mesh.h"

namespace Engine
{
	class Plane : public Mesh
	{
	private:
		std::optional<std::vector<std::string>> diffusePath, specularPath;

	public:
		Plane(std::optional<std::vector<std::string>> diffuse = std::nullopt,
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		Plane(const Core::Shader& shader, 
			std::optional<std::vector<std::string>> diffuse = std::nullopt,
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		virtual ~Plane() = default;

		void Render() override;
		void Update() override;

	private:
		void Initialize();
	};
}

#endif
