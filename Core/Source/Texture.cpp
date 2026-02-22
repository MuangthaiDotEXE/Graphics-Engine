#include "Texture.h"

void Core::Texture::LoadSingle(const std::string& texture, std::string type, GLuint slot, GLenum format, GLenum pixelType)
{
	this->type = type;
	this->unit = slot;
	textureID.clear();
	textureID.emplace_back(LoadTexture(texture, slot, format, pixelType));
}

void Core::Texture::LoadMultiple(const std::vector<std::string>& textures, std::string type, GLuint slot, GLenum format, GLenum pixelType)
{
	this->type = type;
	this->unit = slot;
	textureID.clear();
	textureID.reserve(textures.size());
	for (const auto& texture: textures)
	{
		textureID.emplace_back(LoadTexture(texture, slot, format, pixelType));
	}
}

Core::Texture::~Texture()
{
	Delete();
}

void Core::Texture::SetUnit(Shader& shader, std::string uniform, GLuint unit)
{
	shader.Activate();
	GLuint textureUniform = glGetUniformLocation(shader.programID, uniform.c_str());
	glUniform1i(textureUniform, unit);
}

void Core::Texture::Bind(size_t index)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, textureID[index]);
}

void Core::Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Core::Texture::Delete()
{
	if (!textureID.empty())
	{
		glDeleteTextures(static_cast<GLsizei>(textureID.size()), textureID.data());
		textureID.clear();
	}
}

size_t Core::Texture::GetSize() const
{
	return textureID.size();
}

GLuint Core::Texture::GetID(size_t index = 0) const
{
	return textureID[index];
}

GLuint Core::Texture::LoadTexture(const std::string& path, GLuint slot, GLenum format, GLenum pixelType)
{
	int width, height, channels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (!bytes)
	{
		std::string errorMessage = std::format("Failed to load texture: {} (STB image loading library)\n", path);
		throw std::exception(errorMessage.c_str());
	}

	GLuint id;
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}
