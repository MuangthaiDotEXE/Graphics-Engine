#include "Sky.h"

GLfloat skyVertices[] =
{
	// positions
	 1.0f, -1.0f,  1.0f,    // Back face bottom left vertex
	-1.0f, -1.0f,  1.0f,    // Back face bottom right vertex
	-1.0f,  1.0f,  1.0f,    // Back face top right vertex
	 1.0f,  1.0f,  1.0f,    // Back face top left vertex

	-1.0f, -1.0f, -1.0f,    // Front face bottom right vertex
	 1.0f, -1.0f, -1.0f,    // Front face bottom left vertex
	 1.0f,  1.0f, -1.0f,    // Front face top left vertex
	-1.0f,  1.0f, -1.0f     // Front face top right vertex
};

GLuint skyIndices[] =
{
	// Right face
	5, 0, 3,
	3, 6, 5,

	// Left face
	1, 4, 7,
	7, 2, 1,

	// Top face
	3, 2, 7,
	7, 6, 3,

	// Bottom face
	5, 4, 1,
	1, 0, 5,

	// Back face
	0, 1, 2,
	2, 3, 0,

	// Front face
	4, 5, 6,
	6, 7, 4
};

Engine::Sky::Sky(std::optional<std::vector<std::string>> cubemaps)
	: shader(ProjectDirectory "/Resource/Shader/Sky/Sky.vert", ProjectDirectory "/Resource/Shader/Sky/Sky.frag"),
	cubemap(std::move(cubemaps))
{
	Initialize();
}

Engine::Sky::Sky(const Core::Shader& shader, std::optional<std::vector<std::string>> cubemaps)
	: shader(shader),
	cubemap(std::move(cubemaps))
{
	Initialize();
}

void Engine::Sky::Render()
{
}

void Engine::Sky::Update()
{
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Engine::Sky::Initialize()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyVertices), skyVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyIndices), skyIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	if (cubemap.has_value())
	{
		for (size_t i = 0; i < 6; ++i)
		{
			int width, height, colorChannels;

			unsigned char* image = stbi_load((*cubemap)[i].c_str(), &width, &height, &colorChannels, 0);
			if (!image)
			{
				throw std::runtime_error(std::format("Failed to load texture with path: {} (STB image library)\n", (*cubemap)[i]));
			}

			stbi_set_flip_vertically_on_load(false);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

			stbi_image_free(image);
		}
	}
}
