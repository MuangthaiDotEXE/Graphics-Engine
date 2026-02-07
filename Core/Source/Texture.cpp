#include "Texture.h"

Core::Texture::Texture(const std::string& texture, GLenum type, GLuint slot, GLenum format, GLenum pixelType)
	: type(type)
{
	int width, height, colorChannels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(texture.c_str(), &width, &height, &colorChannels, 0);

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(type, textureID);

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(type, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);
	glGenerateMipmap(type);

	stbi_image_free(bytes);

	glBindTexture(type, 0);
}

Core::Texture::~Texture()
{
	Delete();
}

GLuint* Core::Texture::Initialize(const std::string textures[], GLenum type, GLuint slot, GLenum format, GLenum pixelType)
{
	size_t count = textures->size() / sizeof(std::string);

	this->type = type; 
	this->texturesID = new GLuint[count];
	glGenTextures(count, texturesID);

	for (size_t i = 0; i < count; i++)
	{
		int width, height, colorChannels;

		stbi_set_flip_vertically_on_load(true);

		unsigned char* bytes = stbi_load((textures[i]).c_str(), &width, &height, &colorChannels, 0);

		glActiveTexture(GL_TEXTURE0 + slot);
		unit = slot;
		glBindTexture(type, texturesID[i]);

		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(type, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);
		glGenerateMipmap(type);

		stbi_image_free(bytes);

		glBindTexture(type, 0);
	}

	this->textureID = *texturesID;
	return texturesID;
}

void Core::Texture::textureUnit(Shader& shader, std::string uniform, GLuint unit)
{
	GLuint textureUniform = glGetUniformLocation(shader.programID, uniform.c_str());
	shader.Activate();
	glUniform1i(textureUniform, unit);
}

void Core::Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, textureID);
}

void Core::Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Core::Texture::Delete()
{
	glDeleteTextures(1, &textureID);
}
