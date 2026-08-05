#pragma once

#ifndef SKY_H
#define SKY_H

#include <string>
#include <format>
#include <vector>
#include <optional>
#include <stdexcept>

#include <glad/gl.h>
#include <stb_image.h>

#include "Graphics/Shader/Shader.h"

namespace Engine
{
	class Sky
	{
	public:
		Core::Shader shader;

		GLuint vao, vbo, ebo, texture;
		std::optional<std::vector<std::string>> cubemap; // Direction: right, left, top, bottom, front, back

	public:
		Sky(std::optional<std::vector<std::string>> cubemaps = std::nullopt);
		Sky(const Core::Shader& shader, 
			std::optional<std::vector<std::string>> cubemaps = std::nullopt
		);
		virtual ~Sky() = default;

		void Render();
		void Update();

	private:
		void Initialize();
	};
}

#endif
