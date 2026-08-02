#pragma once

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
#include <array>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "Mesh.h"

namespace Engine
{
	class Triangle : public Mesh
	{
	private:
		std::optional<std::vector<std::string>> diffusePath, specularPath;

	public:
		Triangle(std::optional<std::vector<std::string>> diffuse = std::nullopt,
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		Triangle(const Core::Shader& shader,
			std::optional<std::vector<std::string>> diffuse = std::nullopt,
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		virtual ~Triangle() = default;

		void Render() override;
		void Update() override;

	private:
		void Initialize();
	};
}

#endif
