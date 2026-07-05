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
	public:
		Pyramid();
		Pyramid(const Core::Shader& shader);
		virtual ~Pyramid() = default;

		void Render() override;
		void Update() override;
	private:
		void Initialize();
	};
}

#endif
