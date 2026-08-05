#include "Triangle.h"

static Vertex triangleVertices[] =
{
            // positions                   // colors                    // textures            // normals
	Vertex{ glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.5f, 1.0f) },    // Bottom left vertex
	Vertex{ glm::vec3( 1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.5f, 1.0f) },    // Bottom right vertex
	Vertex{ glm::vec3( 0.0f,  1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 0.5f, 1.0f) }     // Top right vertex
};

static GLuint triangleIndices[] =
{
	// Triangle
	0, 1, 2,
};

std::vector<Vertex> triangleVerts(triangleVertices, triangleVertices + sizeof(triangleVertices) / sizeof(Vertex));
std::vector<GLuint> triangleInds(triangleIndices, triangleIndices + sizeof(triangleIndices) / sizeof(GLuint));

Engine::Triangle::Triangle(std::optional<std::vector<std::string>> diffuse, 
	std::optional<std::vector<std::string>> specular
)
	: Mesh(ProjectDirectory "/Resource/Shader/Mesh/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh/Mesh.frag", triangleVerts, triangleInds, diffuse, specular),
	diffusePath(std::move(diffuse)),
	specularPath(std::move(specular))
{
	Initialize();
}

Engine::Triangle::Triangle(const Core::Shader& shader, 
	std::optional<std::vector<std::string>> diffuse, 
	std::optional<std::vector<std::string>> specular
)
	: Mesh(shader, triangleVerts, triangleInds, diffuse, specular),
	diffusePath(std::move(diffuse)),
	specularPath(std::move(specular))
{
	Initialize();
}

void Engine::Triangle::Render()
{
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Triangle::Update()
{
	shader.Activate();
	vao.Bind();

	glUniform1i(glGetUniformLocation(shader.programID, "hasDiffuse"), diffusePath.has_value() ? GL_TRUE : GL_FALSE);
	glUniform1i(glGetUniformLocation(shader.programID, "hasSpecular"), specularPath.has_value() ? GL_TRUE : GL_FALSE);

	if (diffusePath.has_value())
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuse.GetID(0));
	}
	if (specularPath.has_value())
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular.GetID(0));
	}

	glDrawElements(GL_TRIANGLES, triangleInds.size(), GL_UNSIGNED_INT, 0);
}

void Engine::Triangle::Initialize()
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
