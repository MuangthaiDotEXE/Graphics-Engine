#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include <string>
#include <cmath>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Mesh.h"

namespace Engine
{
	class Sphere : public Mesh
	{
	private:
		GLsizei indexCount;

	public:
		Sphere();
		Sphere(const Core::Shader& shader);
		virtual ~Sphere() = default;

		void Render() override;
		void Update() override;

	private:
		void Initialize();
	};
}

#endif
