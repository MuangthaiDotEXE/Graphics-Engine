#pragma once

#ifndef PLANE_H
#define PLANE_H

#include "Mesh.h"

namespace Engine
{
	class Plane final : public Mesh
	{
	public:
		Plane();
		virtual ~Plane();

		void Render() override;
		void Update() override;
	};
}

#endif
