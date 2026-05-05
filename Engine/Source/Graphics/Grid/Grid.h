#pragma once

#ifndef GRID_H
#define GRID_H

#include <string>

#include "Graphics/Shader/Shader.h"

namespace Engine
{
	class Grid
	{
	public:
		Core::Shader shader;

	public:
		Grid();
		virtual ~Grid();

		void Render();
		void Update();
	};
}

#endif
