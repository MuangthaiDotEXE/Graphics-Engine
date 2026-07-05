#include "Plane.h"

static Vertex planeVertices[] =
{
	        // positions					// colors					 // textures			// normals
	Vertex{ glm::vec3(-1.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },    // Bottom left vertex
	Vertex{ glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },    // Bottom right vertex
	Vertex{ glm::vec3( 1.0f,  0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },    // Top right vertex
	Vertex{ glm::vec3(-1.0f,  0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }     // Top left vertex
};

static GLuint planeIndices[] =
{
	// Plane
	0, 1, 2,
	2, 3, 0
};

std::string planeTexture = ProjectDirectory "/Asset/Texture/Green_Brick_Texture.png";
std::string planeSpecular = ProjectDirectory "/Asset/Specular/Green_Brick_Texture_specular.png";

std::vector<Vertex> planeVerts(planeVertices, planeVertices + sizeof(planeVertices) / sizeof(Vertex));
std::vector<GLuint> planeInds(planeIndices, planeIndices + sizeof(planeIndices) / sizeof(GLuint));

Engine::Plane::Plane()
	: Mesh(ProjectDirectory "/Resource/Shader/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh.frag", 
		planeVerts, planeInds, Core::Texture(), Core::Texture())
{
	Initialize();
}

Engine::Plane::Plane(const Core::Shader& shader)
	: Mesh(shader, planeVerts, planeInds, Core::Texture(), Core::Texture())
{
	Initialize();
}

void Engine::Plane::Render()
{
	shader.Activate();

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Plane::Update()
{
	shader.Activate();
	vao.Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse.GetID(0));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specular.GetID(0));

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

	diffuse.LoadSingle(planeTexture, "diffuse", 0);
	specular.LoadSingle(planeSpecular, "specular", 1);

	diffuse.SetUnit(shader, "diffuseSampler", 0);
	specular.SetUnit(shader, "specularSampler", 1);
}
