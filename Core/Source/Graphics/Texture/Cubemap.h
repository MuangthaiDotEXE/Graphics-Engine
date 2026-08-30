#pragma once

#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <string>
#include <format>
#include <vector>
#include <optional>
#include <stdexcept>

#include <glad/gl.h>
#include <stb_image.h>

#include "Graphics/Shader/Shader.h"

namespace Core
{
	class Cubemap
	{
	private:
		GLuint cubemapID;
		std::string type;

	public:
		Cubemap(std::optional<std::vector<std::string>> cubemaps, std::string type);
		virtual ~Cubemap();

		void Bind();
		void Unbind();

		GLuint GetID() const;
	};
}

#endif
