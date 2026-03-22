#include "Cube.h"

vertex cubeVertices[] =
{
			// positions					// colors					 // textures			// normals
	vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },   // Front face top left vertex
	vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },	// Front face top right vertex
	vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },	// Front face bottom right vertex
	vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f) },	// Front face bottom left vertex

	vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },   // Right face top left vertex
	vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },	// Right face top right vertex
	vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },	// Right face bottom right vertex
	vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f) },	// Right face bottom left vertex

	vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },   // Back face top left vertex
	vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },	// Back face top right vertex
	vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },	// Back face bottom right vertex
	vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f) },	// Back face bottom left vertex

	vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },   // Left face top left vertex
	vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },	// Left face top right vertex
	vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },	// Left face bottom right vertex
	vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f) },	// Left face bottom left vertex

	vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  1.0f,  0.0f) },   // Top face top left vertex
	vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  1.0f,  0.0f) },	// Top face top right vertex
	vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f) },	// Top face bottom right vertex
	vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f) },	// Top face bottom left vertex

	vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },   // Bottom face top left vertex
	vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },	// Bottom face top right vertex
	vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f) },	// Bottom face bottom right vertex
	vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f) }	// Bottom face bottom left vertex
};

GLuint cubeIndices[] =
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

static const std::array<std::string, 6> cubeTexture
{
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png",   // Front face
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png",   // Right face
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png",   // Back face
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png",   // Left face
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png",   // Top face
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png"    // Bottom face
};

static const std::array<std::string, 6> cubeSpecular
{
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png",  // Front face
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png",	// Right face
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png",	// Back face
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png",	// Left face
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png",	// Top face
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png" 	// Bottom face
};

std::vector<vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(vertex));
std::vector<GLuint> cubeInds(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));

Engine::Cube::Cube()
	: Mesh(ProjectDirectory "/Resource/Shader/Cube.vert", ProjectDirectory "/Resource/Shader/Cube.frag", cubeVerts, cubeInds, Core::Texture(), Core::Texture())
{
	Initialize();
}

Engine::Cube::Cube(const Core::Shader& shader)
	: Mesh(shader, cubeVerts, cubeInds, Core::Texture(), Core::Texture())
{
	Initialize();
}

Engine::Cube::~Cube()
{
}

void Engine::Cube::Render()
{
	shader.Activate();

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Cube::Update()
{
	shader.Activate();
	vao.Bind();

	for (size_t i = 0; i < 6; i++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuse.GetID(i));

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular.GetID(i));

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

	diffuse.LoadMultiple({ cubeTexture.begin(), cubeTexture.end() }, "diffuse", 0);
	specular.LoadMultiple({ cubeSpecular.begin(), cubeSpecular.end() }, "specular", 1);

	diffuse.SetUnit(this->shader, "diffuseSampler", 0);
	specular.SetUnit(this->shader, "specularSampler", 1);
}
