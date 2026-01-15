#include "Mesh.h"

GLfloat vertices[] =
{
	// meshPosition		   // meshColor		   // meshTexture
	-1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 1.0f,   // Front face top left vertex
	 1.0f,  1.0f,  1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // Front face top right vertex
	 1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // Front face bottom right vertex
	-1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Front face bottom left vertex

	-1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // Right face top left vertex
	-1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // Right face top right vertex
	-1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // Right face bottom right vertex
	-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // Right face bottom left vertex

	 1.0f,  1.0f, -1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // Back face top left vertex
	-1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // Back face top right vertex
	-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // Back face bottom right vertex
	 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // Back face bottom left vertex

	 1.0f,  1.0f,  1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   // Left face top left vertex
	 1.0f,  1.0f, -1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // Left face top right vertex
	 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // Left face bottom right vertex
	 1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Left face bottom left vertex

	-1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // Top face top left vertex
	 1.0f,  1.0f, -1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // Top face top right vertex
	 1.0f,  1.0f,  1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // Top face bottom right vertex
	-1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // Top face bottom left vertex

	-1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,   // Bottom face top left vertex
	 1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 1.0f,   1.0f, 1.0f,   // Bottom face top right vertex
	 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // Bottom face bottom right vertex
	-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f    // Bottom face bottom left vertex
};

GLuint indices[] =
{
	// Front face
	 0,  1,  3,
	 1,  2,  3,

	// Right face
	 4,  5,  7,
	 5,  6,  7,

	// Back face
	 8,  9, 11,
	 9, 10, 11,

	// Left face
	12, 13, 15,
	13, 14, 15,

	// Top face
	16, 17, 19,
	17, 18, 19,

	// Bottom face
	20, 21, 23,
	21, 22, 23
};

std::string textureImages[] =
{
	ProjectDirectory "/Asset/Texture/Texture.png",
	ProjectDirectory "/Asset/Texture/Texture.png",
	ProjectDirectory "/Asset/Texture/Texture.png",
	ProjectDirectory "/Asset/Texture/Texture.png",
	ProjectDirectory "/Asset/Texture/Texture.png",
	ProjectDirectory "/Asset/Texture/Texture.png"
};

Engine::Mesh::Mesh()
	: shader(ProjectDirectory "/Resource/Shader/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh.frag"), 
	vao(), vbo(vertices, sizeof(vertices)), ebo(indices, sizeof(indices)), texture()
{
	vao.Bind();
	vbo.Bind();
	ebo.Bind();

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttributes(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	textures = texture.Initialize(textureImages, sizeof(textureImages) / sizeof(std::string), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.textureUnit(shader, "textureSampler", 0);
}

Engine::Mesh::~Mesh()
{
}

void Engine::Mesh::Render()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Mesh::Update()
{
	shader.Activate();
	texture.Bind();
	vao.Bind();

	for (int i = 0; i < sizeof(textureImages) / sizeof(std::string); i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(GLuint)));
	}
}
