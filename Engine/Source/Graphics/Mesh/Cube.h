#pragma once

#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <string>

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
