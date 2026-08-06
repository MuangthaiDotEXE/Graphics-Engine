#include "Cubemap.h"

Core::Cubemap::Cubemap(std::optional<std::vector<std::string>> cubemaps, std::string type)
	: type(type)
{
	glGenTextures(1, &cubemapID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	if (cubemaps.has_value())
	{
		for (size_t i = 0; i < cubemaps.value().size(); ++i)
		{
			int width, height, colorChannels;

			unsigned char* image = stbi_load((*cubemaps)[i].c_str(), &width, &height, &colorChannels, 0);
			if (!image)
			{
				throw std::runtime_error(std::format("Failed to load texture with path: {} (STB image library)\n", (*cubemaps)[i]));
			}

			stbi_set_flip_vertically_on_load(false);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

			stbi_image_free(image);
		}
	}
}

void Core::Cubemap::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
}

void Core::Cubemap::Unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLuint Core::Cubemap::GetID() const
{
	return cubemapID;
}
