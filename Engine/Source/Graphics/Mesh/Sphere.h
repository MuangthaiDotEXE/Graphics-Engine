#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include <string>
#include <vector>

#include "Mesh.h"

namespace Engine
{
	class Sphere : public Mesh
	{
	public:
		Sphere();
		Sphere(const Core::Shader& shader);
		virtual ~Sphere();

		void Render();
		void Update();

	private:
		void Initialize();
	};
}

#endif
