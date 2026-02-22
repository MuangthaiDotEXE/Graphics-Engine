#pragma once

#ifndef CUBE_H
#define CUBE_H

#include <string>
#include <array>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "Mesh.h"

namespace Engine
{
	class Cube : public Mesh
	{
	public:
		Cube();
		virtual ~Cube();

		void Render() override;
		void Update() override;
	};
}

#endif
