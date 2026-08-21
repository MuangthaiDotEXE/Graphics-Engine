#pragma once

#ifndef CUBE_H
#define CUBE_H

#include <string>
#include <array>
#include <vector>
#include <optional>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "Mesh.h"

namespace Engine
{
	class Cube : public Mesh
	{
	public:
		Cube(std::optional<std::vector<std::string>> diffuse = std::nullopt, 
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		Cube(const Core::Shader& shader, 
			std::optional<std::vector<std::string>> diffuse = std::nullopt, 
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		virtual ~Cube() = default;

		void Render() override;
		void Update() override;

	private:
		void Initialize();
	};
}

#endif
