#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

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
	class Texture
	{
	private:
		std::vector<GLuint> textureID;
		std::string type;
		GLuint unit;

	public:
		Texture() = default;
		Texture(std::optional<std::string> texture, const std::string& type, GLuint slot);
		Texture(std::optional<std::vector<std::string>> textures, const std::string& type, GLuint slot);
		virtual ~Texture();

		void SetUnit(Shader& shader, const std::string& uniform, GLuint unit);
		void Bind(size_t index = 0);
		void Unbind();
		void Delete();

		GLuint GetID(size_t index = 0) const;
		size_t GetSize() const;

	private:
		static GLuint LoadTexture(const std::string& path, GLuint slot);
	};
}

#endif
