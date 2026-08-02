#include "Texture.h"

Core::Texture::Texture(std::optional<std::string> texture, const std::string& type, GLuint slot)
	: type(type),
	unit(slot)
{
	if (texture.has_value())
	{
		textureID.clear();
		textureID.emplace_back(LoadTexture(texture.value(), slot));
	}
}

Core::Texture::Texture(std::optional<std::vector<std::string>> textures, const std::string& type, GLuint slot)
	: type(type),
	unit(slot)
{
	if (textures.has_value())
	{
		textureID.clear();
		textureID.reserve(textures->size());

		for (const auto& texture : textures.value())
		{
			textureID.emplace_back(LoadTexture(texture, slot));
		}
	}
}

Core::Texture::~Texture()
{
	Delete();
}

void Core::Texture::SetUnit(Shader& shader, const std::string& uniform, GLuint unit)
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

GLuint Core::Texture::LoadTexture(const std::string& path, GLuint slot)
{
	int width, height, channels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (!bytes)
	{
		throw std::runtime_error(std::format("Failed to load texture with path: {} (STB image library)\n", path));
	}

	GLuint id;
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (channels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	}
	else if (channels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	}
	else if (channels == 1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
	}
	else
	{
		throw std::invalid_argument(std::format(R"(Failed to recognize texture type (OpenGL graphics API)
	path: {}
	width: {}
	height: {}
	color channels: {})", path, width, height, channels));
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}
