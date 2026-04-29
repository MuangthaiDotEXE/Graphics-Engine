#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/VAO.h"
#include "Graphics/Shader/VBO.h"
#include "Graphics/Shader/EBO.h"

namespace Engine
{
	class Light
	{
	public:
		Core::Shader shader;
		Core::VAO vao;
		Core::VBO vbo;
		Core::EBO ebo;

		std::string name = "Light";

	public:
		struct LightTransform
	{
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 rotation = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);

		glm::mat4 GetMatrix() const;
	};
		
		LightTransform transform;

	public:
		Light();
		virtual ~Light();

		void Render();
		void Update();
	};
}

#endif
