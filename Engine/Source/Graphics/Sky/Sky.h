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
#include "Graphics/Shader/VAO.h"
#include "Graphics/Shader/VBO.h"
#include "Graphics/Shader/EBO.h"
#include "Graphics/Texture/Cubemap.h"

namespace Engine
{
	class Sky    // Direction: right, left, top, bottom, front, back
	{
	public:
		Core::Shader shader;
		Core::VAO vao;
		Core::VBO vbo;
		Core::EBO ebo;
		Core::Cubemap cubemap;

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
