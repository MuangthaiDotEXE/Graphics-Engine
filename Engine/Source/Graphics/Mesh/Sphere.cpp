#include "Sphere.h"

static const int SPHERE_SECTORS = 32;
static const int SPHERE_STACKS = 16;
static const float SPHERE_RADIUS = 1.0f;

static std::vector<Vertex> GenerateSphereVertices(float radius, int sectors, int stacks)
{
	std::vector<Vertex> vertices;
	vertices.reserve((stacks + 1) * (sectors + 1));

	const float sectorStep = 2.0f * glm::pi<float>() / sectors;
	const float stackStep = glm::pi<float>() / stacks;

	for (size_t i = 0; i <= stacks; ++i)
	{
		const float stackAngle = glm::pi<float>() / 2.0f - i * stackStep;

		const float xz = radius * glm::cos(stackAngle);
		const float y = radius * glm::sin(stackAngle);

		for (size_t j = 0; j <= sectors; ++j)
		{
			const float sectorAngle = j * sectorStep;

			const float x = xz * glm::cos(sectorAngle);
			const float z = xz * glm::sin(sectorAngle);

			const glm::vec3 position(x, y, z);
			const glm::vec3 normal = glm::normalize(position);
			const glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
			const glm::vec2 textureCoordinate = glm::vec2(
				(float)j / sectors,
				(float)i / stacks
			);

			vertices.emplace_back(Vertex{ position, color, textureCoordinate, normal });
		}
	}

	return vertices;
}

static std::vector<GLuint> GenerateSphereIndices(int sectors, int stacks)
{
	std::vector<GLuint> indices;
	indices.reserve((stacks - 1) * sectors * 6);

	for (size_t i = 0; i < stacks; ++i)
	{
		for (size_t j = 0; j < sectors; ++j)
		{
			const GLuint k1 = i * (sectors + 1) + j;
			const GLuint k2 = k1 + sectors + 1;

			if (i != 0)
			{
				indices.emplace_back(k1);
				indices.emplace_back(k1 + 1);
				indices.emplace_back(k2);
			}

			if (i != stacks - 1)
			{
				indices.emplace_back(k1 + 1);
				indices.emplace_back(k2 + 1);
				indices.emplace_back(k2);
			}
		}
	}

	return indices;
}

static std::vector<Vertex> sphereVerts = GenerateSphereVertices(SPHERE_RADIUS, SPHERE_SECTORS, SPHERE_STACKS);
static std::vector<GLuint> sphereInds = GenerateSphereIndices(SPHERE_SECTORS, SPHERE_STACKS);

static const std::string sphereTexture = ProjectDirectory "/Asset/Texture/Earth_Color_Map.png";
static const std::string sphereSpecular = ProjectDirectory "/Asset/Specular/Earth_Bump_Map.png";

Engine::Sphere::Sphere()
	: Mesh(ProjectDirectory "/Resource/Shader/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh.frag",
		sphereVerts, sphereInds, Core::Texture(), Core::Texture()),
		indexCount(static_cast<GLsizei>(sphereInds.size()))
{
	Initialize();
}

Engine::Sphere::Sphere(const Core::Shader& shader)
	: Mesh(shader, sphereVerts, sphereInds, Core::Texture(), Core::Texture()),
	indexCount(static_cast<GLsizei>(sphereInds.size()))
{
	Initialize();
}

void Engine::Sphere::Render()
{
	shader.Activate();
	
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Sphere::Update()
{
	shader.Activate();
	vao.Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse.GetID(0));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specular.GetID(0));

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Engine::Sphere::Initialize()
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

	diffuse.LoadMultiple({ sphereTexture }, "diffuse", 0);
	specular.LoadMultiple({ sphereSpecular }, "specular", 1);

	diffuse.SetUnit(shader, "diffuseSampler", 0);
	specular.SetUnit(shader, "specularSampler", 1);
}
