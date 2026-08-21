#pragma once

#ifndef QUAD_H
#define QUAD_H

#include <string>
#include <array>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "Mesh.h"

namespace Engine
{
	class Quad : public Mesh
	{
	public:
		Quad(std::optional<std::vector<std::string>> diffuse = std::nullopt,
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		Quad(const Core::Shader& shader,
			std::optional<std::vector<std::string>> diffuse = std::nullopt,
			std::optional<std::vector<std::string>> specular = std::nullopt
		);
		virtual ~Quad() = default;

		void Render() override;
		void Update() override;

	private:
		void Initialize();
	};
}

#endif
