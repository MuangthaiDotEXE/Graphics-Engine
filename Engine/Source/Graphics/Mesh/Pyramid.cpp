#include "Pyramid.h"

static Vertex pyramidVertices[] =
{
		// positions                        // colors                    // textures            // normals
	Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  0.5f,  1.0f) },    // Front face bottom left vertex
	Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  0.5f,  1.0f) },    // Front face bottom right vertex
	Vertex{ glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 1.0f), glm::vec3( 0.0f,  0.5f,  1.0f) },    // Front face top vertex
	
	Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  0.5f, -1.0f) },    // Back face bottom left vertex
	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  0.5f, -1.0f) },    // Back face bottom right vertex
	Vertex{ glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 1.0f), glm::vec3( 0.0f,  0.5f, -1.0f) },    // Back face top right vertex
	
	Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 1.0f,  0.5f,  0.0f) },    // Left face bottom left vertex
	Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 1.0f,  0.5f,  0.0f) },    // Left face bottom right vertex
	Vertex{ glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.5f, 1.0f), glm::vec3( 1.0f,  0.5f,  0.0f) },    // Left face top right vertex
	
	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f,  0.5f,  0.0f) },    // Right face bottom left vertex
	Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f,  0.5f,  0.0f) },    // Right face bottom right vertex
	Vertex{ glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.5f, 1.0f), glm::vec3(-1.0f,  0.5f,  0.0f) },    // Right face top right vertex
	
	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },    // Bottom face bottom left vertex
	Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },    // Bottom face bottom right vertex
	Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },    // Bottom face top right vertex
	Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f) }     // Bottom face top left vertex
};

static GLuint pyramidIndices[] =
{
	// Front face
	 0,  1,  2,

	// Back face
	 3,  4,  5,

	// Left face
	 6,  7,  8,

	// Right face
	 9, 10, 11,

	// Bottom face
	12, 13, 14,
	14, 15, 12
};

std::vector<Vertex> pyramidVerts(pyramidVertices, pyramidVertices + sizeof(pyramidVertices) / sizeof(Vertex));
std::vector<GLuint> pyramidInds(pyramidIndices, pyramidIndices + sizeof(pyramidIndices) / sizeof(GLuint));

Engine::Pyramid::Pyramid(std::optional<std::vector<std::string>> diffuse,
	std::optional<std::vector<std::string>> specular
)
	: Mesh(ProjectDirectory "/Resource/Shader/Mesh/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh/Mesh.frag", pyramidVerts, pyramidInds, diffuse, specular),
	diffusePath(std::move(diffuse)),
	specularPath(std::move(specular))
{
	Initialize();
}

Engine::Pyramid::Pyramid(const Core::Shader& shader,
	std::optional<std::vector<std::string>> diffuse,
	std::optional<std::vector<std::string>> specular
)
	: Mesh(shader, pyramidVerts, pyramidInds, diffuse, specular),
	diffusePath(std::move(diffuse)),
	specularPath(std::move(specular))
{
	Initialize();
}

void Engine::Pyramid::Render()
{
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Pyramid::Update()
{
	shader.Activate();
	vao.Bind();

	glUniform1i(glGetUniformLocation(shader.programID, "hasDiffuse"), diffusePath.has_value() ? GL_TRUE : GL_FALSE);
	glUniform1i(glGetUniformLocation(shader.programID, "hasSpecular"), specularPath.has_value() ? GL_TRUE : GL_FALSE);

	for (size_t i = 0; i < 5; ++i)
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

		if (i < 4)
		{
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(i * 3 * sizeof(GLuint)));
		}
		else
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(GLuint)));
		}
	}
}

void Engine::Pyramid::Initialize()
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
