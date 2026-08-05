#include "Cube.h"

static Vertex cubeVertices[] =
{
            // positions                    // colors                    // textures            // normals
	Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },    // Front face bottom left vertex
	Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },    // Front face bottom right vertex
	Vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },    // Front face top right vertex
	Vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },    // Front face top left vertex

	Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },    // Back face bottom left vertex
	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },    // Back face bottom right vertex
	Vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },    // Back face top right vertex
	Vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },    // Back face top left vertex

	Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },    // Left face bottom left vertex
	Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },    // Left face bottom right vertex
	Vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },    // Left face top right vertex
	Vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },    // Left face top left vertex

	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },    // Right face bottom left vertex
	Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },    // Right face bottom right vertex
	Vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },    // Right face top right vertex
	Vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },    // Right face top left vertex

	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },    // Bottom face bottom left vertex
	Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },    // Bottom face bottom right vertex
	Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },    // Bottom face top right vertex
	Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },    // Bottom face top left vertex

	Vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f) },    // Top face bottom left vertex
	Vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f) },    // Top face bottom right vertex
	Vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  1.0f,  0.0f) },    // Top face top right vertex
	Vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  1.0f,  0.0f) }     // Top face top left vertex
};

static GLuint cubeIndices[] =
{
	// Front face
	 0,  1,  2,
	 2,  3,  0,

	// Back face
	 4,  5,  6,
	 6,  7,  4,

	// Left face
	 8,  9, 10,
	10, 11,  8,

	// Right face
	12, 13, 14,
	14, 15, 12,

	// Bottom face
	16, 17, 18,
	18, 19, 16,

	// Top face
	20, 21, 22,
	22, 23, 20
};

std::vector<Vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
std::vector<GLuint> cubeInds(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));

Engine::Cube::Cube(std::optional<std::vector<std::string>> diffuse,
	std::optional<std::vector<std::string>> specular
)
	: Mesh(ProjectDirectory "/Resource/Shader/Mesh/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh/Mesh.frag", cubeVerts, cubeInds, diffuse, specular),
	diffusePath(std::move(diffuse)),
	specularPath(std::move(specular))
{
	Initialize();
}

Engine::Cube::Cube(const Core::Shader& shader,
	std::optional<std::vector<std::string>> diffuse,
	std::optional<std::vector<std::string>> specular
)
	: Mesh(shader, cubeVerts, cubeInds, diffuse, specular),
	diffusePath(std::move(diffuse)),
	specularPath(std::move(specular))
{
	Initialize();
}

void Engine::Cube::Render()
{
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Cube::Update()
{
	shader.Activate();
	vao.Bind();

	glUniform1i(glGetUniformLocation(shader.programID, "hasDiffuse"), diffusePath.has_value() ? GL_TRUE : GL_FALSE);
	glUniform1i(glGetUniformLocation(shader.programID, "hasSpecular"), specularPath.has_value() ? GL_TRUE : GL_FALSE);

	for (size_t i = 0; i < 6; ++i)
	{
		if (diffusePath.has_value())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuse.GetID(i));
		}
		if (specularPath.has_value())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, specular.GetID(i));
		}

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(GLuint)));
	}
}

void Engine::Cube::Initialize()
{
	vao.Bind();
	vbo.Bind();
	ebo.Bind();

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttributes(vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.LinkAttributes(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	if (diffusePath.has_value())
	{
		diffuse.SetUnit(shader, "diffuseSampler", 0);
	}
	if (specularPath.has_value())
	{
		specular.SetUnit(shader, "specularSampler", 1);
	}
}
