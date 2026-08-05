#include "Plane.h"

static Vertex planeVertices[] =
{
	        // positions                   // colors                    // textures            // normals
	Vertex{ glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },    // Bottom left vertex
	Vertex{ glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },    // Bottom right vertex
	Vertex{ glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },    // Top right vertex
	Vertex{ glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }     // Top left vertex
};

static GLuint planeIndices[] =
{
	// Plane
	0, 1, 2,
	2, 3, 0
};

std::vector<Vertex> planeVerts(planeVertices, planeVertices + sizeof(planeVertices) / sizeof(Vertex));
std::vector<GLuint> planeInds(planeIndices, planeIndices + sizeof(planeIndices) / sizeof(GLuint));

Engine::Plane::Plane(std::optional<std::vector<std::string>> diffuse,
	std::optional<std::vector<std::string>> specular
)
	: Mesh(ProjectDirectory "/Resource/Shader/Mesh/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh/Mesh.frag", planeVerts, planeInds, diffuse, specular),
	diffusePath(std::move(diffuse)),
	specularPath(std::move(specular))
{
	Initialize();
}

Engine::Plane::Plane(const Core::Shader& shader, 
	std::optional<std::vector<std::string>> diffuse,
	std::optional<std::vector<std::string>> specular
)
	: Mesh(shader, planeVerts, planeInds, diffuse, specular),
	diffusePath(std::move(diffuse)),
	specularPath(std::move(specular))
{
	Initialize();
}

void Engine::Plane::Render()
{
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Plane::Update()
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

	glDrawElements(GL_TRIANGLES, planeInds.size(), GL_UNSIGNED_INT, 0);
}

void Engine::Plane::Initialize()
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
