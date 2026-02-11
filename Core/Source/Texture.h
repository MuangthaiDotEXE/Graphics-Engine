#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <glad/gl.h>
#include <stb_image.h>

#include "Shader.h"

namespace Core
{
	class Texture
	{
	private:
		GLuint textureID;
		GLuint* texturesID;
		const char* type;
		GLuint unit;

	public:
		Texture() = default;
		Texture(const std::string& texture, const char* type, GLuint slot, GLenum format, GLenum pixelType);
		virtual ~Texture();

		GLuint* Initialize(const std::string textures[], const char* type, GLuint slot, GLenum format, GLenum pixelType);
		void textureUnit(Shader& shader, std::string uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
	};
}

#endif
