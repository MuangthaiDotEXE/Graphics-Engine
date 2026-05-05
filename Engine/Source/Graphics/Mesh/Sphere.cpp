#include "Sphere.h"

Vertex sphereVertices[1]
{
	// Add later
};

GLuint sphereIndices[1]
{
	// Add later
};

static const std::string sphereTexture = ""; // Add later
static const std::string sphereSpecular = ""; // Add later

std::vector<Vertex> sphereVerts(sphereVertices, sphereVertices + sizeof(sphereVertices) / sizeof(Vertex));
std::vector<GLuint> sphereInds(sphereIndices, sphereIndices + sizeof(sphereIndices) / sizeof(GLuint));

Engine::Sphere::Sphere()
	: Mesh(ProjectDirectory "/Resource/Shader/Sphere.vert", ProjectDirectory "/Resource/Shader/Sphere.frag", sphereVerts, sphereInds, Core::Texture(), Core::Texture())
{
	Initialize();
}

Engine::Sphere::Sphere(const Core::Shader& shader)
	: Mesh(shader, sphereVerts, sphereInds, Core::Texture(), Core::Texture())
{
	Initialize();
}

Engine::Sphere::~Sphere()
{
}

void Engine::Sphere::Render()
{
}

void Engine::Sphere::Update()
{
}

void Engine::Sphere::Initialize()
{
}
