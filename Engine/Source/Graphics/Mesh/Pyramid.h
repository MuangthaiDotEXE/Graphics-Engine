#pragma once

#ifndef PYRAMID_H
#define PYRAMID_H

#include <string>
#include <array>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "Mesh.h"

namespace Engine
{
	class Pyramid : public Mesh
	{
	private:
		std::optional<std::vector<std::string>> diffusePath, specularPath;

	public:
		Pyramid(std::optional<std::vector<std::string>> diffuse = std::nullopt,
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		Pyramid(const Core::Shader& shader, 
			std::optional<std::vector<std::string>> diffuse = std::nullopt,
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		virtual ~Pyramid() = default;

		void Render() override;
		void Update() override;
	private:
		void Initialize();
	};
}

#endif
