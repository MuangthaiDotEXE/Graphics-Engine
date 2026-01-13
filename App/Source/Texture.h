#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <filesystem>
#include <string>

#include <glad/gl.h>
#include <stb_image.h>

#include "Shader.h"

namespace App
{
	class Texture
	{
	private:
		GLuint textureID;
		GLuint* texturesID;
		GLenum type;

	public:
		Texture() = default;
		Texture(const std::string& texture, GLenum type, GLenum slot, GLenum format, GLenum pixelType);
		virtual ~Texture();

		GLuint* Initialize(const std::string textures[], GLsizei count, GLenum type, GLenum slot, GLenum format, GLenum pixelType);
		void textureUnit(Shader& shader, std::string uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
	};
}

#endif
