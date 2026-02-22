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
	public:
		Plane();
		virtual ~Plane();

		void Render() override;
		void Update() override;
	};
}

#endif
