#pragma once

#ifndef CUBE_H
#define CUBE_H

#include "Mesh.h"

namespace Engine
{
	class Cube final : public Mesh
	{
	public:
		Cube();
		virtual ~Cube();

		void Render() override;
		void Update() override;
	};
}

#endif
