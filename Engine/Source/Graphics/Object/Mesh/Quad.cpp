#include "Quad.h"

static Vertex quadVertices[] =
{
	        // positions                   // colors                    // textures            // normals
	Vertex{ glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },    // Bottom left vertex
	Vertex{ glm::vec3( 1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },    // Bottom right vertex
	Vertex{ glm::vec3( 1.0f,  1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },    // Top right vertex
	Vertex{ glm::vec3(-1.0f,  1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }     // Top left vertex
};

static GLuint quadIndices[] =
{
	// Quad
	0, 1, 2,
	2, 3, 0
};

std::vector<Vertex> quadVerts(quadVertices, quadVertices + sizeof(quadVertices) / sizeof(Vertex));
std::vector<GLuint> quadInds(quadIndices, quadIndices + sizeof(quadIndices) / sizeof(GLuint));

Engine::Quad::Quad(std::optional<std::vector<std::string>> diffuse, 
	std::optional<std::vector<std::string>> specular
)
	: Mesh(ProjectDirectory "/Resource/Shader/Mesh/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh/Mesh.frag", quadVerts, quadInds, diffuse, specular)
{
	Initialize();
}

Engine::Quad::Quad(const Core::Shader& shader, 
	std::optional<std::vector<std::string>> diffuse, 
	std::optional<std::vector<std::string>> specular
)
	: Mesh(shader, quadVerts, quadInds, diffuse, specular)
{
	Initialize();
}

void Engine::Quad::Render()
{
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Quad::Update()
{
	shader.Activate();
	vao.Bind();

	glUniform1i(glGetUniformLocation(shader.programID, "hasDiffuse"), diffusePath ? GL_TRUE : GL_FALSE);
	glUniform1i(glGetUniformLocation(shader.programID, "hasSpecular"), specularPath ? GL_TRUE : GL_FALSE);

	if (diffusePath)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuse.GetID(0));
	}

	if (specularPath)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular.GetID(0));
	}

	glDrawElements(GL_TRIANGLES, quadInds.size(), GL_UNSIGNED_INT, 0);
}

void Engine::Quad::Initialize()
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

	if (diffusePath)
	{
		diffuse.SetUnit(shader, "diffuseSampler", 0);
	}
	if (specularPath)
	{
		specular.SetUnit(shader, "specularSampler", 1);
	}
}
