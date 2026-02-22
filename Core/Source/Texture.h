#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <format>
#include <vector>
#include <stdexcept>

#include <glad/gl.h>
#include <stb_image.h>

#include "Shader.h"

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
		virtual ~Texture();

		void LoadSingle(const std::string& texture, std::string type, GLuint slot, GLenum format, GLenum pixelType);
		void LoadMultiple(const std::vector<std::string>& textures, std::string type, GLuint slot, GLenum format, GLenum pixelType);
		void SetUnit(Shader& shader, std::string uniform, GLuint unit);
		void Bind(size_t index);
		void Unbind();
		void Delete();

		GLuint GetID(size_t index) const;
		size_t GetSize() const;

	private:
		static GLuint LoadTexture(const std::string& path, GLuint slot, GLenum format, GLenum pixelType);
	};
}

#endif
