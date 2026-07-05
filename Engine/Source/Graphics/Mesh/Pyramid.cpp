#include "Pyramid.h"

static Vertex pyramidVertices[] =
{
		// positions					// colors					 // textures			// normals
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

static const std::array<std::string, 5> pyramidTexture
{
	ProjectDirectory "/Asset/Texture/Sand_Stone_Texture.png",   // Front face
	ProjectDirectory "/Asset/Texture/Sand_Stone_Texture.png",   // Right face
	ProjectDirectory "/Asset/Texture/Sand_Stone_Texture.png",   // Back face
	ProjectDirectory "/Asset/Texture/Sand_Stone_Texture.png",   // Left face
	ProjectDirectory "/Asset/Texture/Sand_Stone_Texture.png"    // Bottom face
};

static const std::array<std::string, 5> pyramidSpecular
{
	ProjectDirectory "/Asset/Specular/Sand_Stone_Texture_specular.png",   // Front face
	ProjectDirectory "/Asset/Specular/Sand_Stone_Texture_specular.png",   // Right face
	ProjectDirectory "/Asset/Specular/Sand_Stone_Texture_specular.png",   // Back face
	ProjectDirectory "/Asset/Specular/Sand_Stone_Texture_specular.png",   // Left face
	ProjectDirectory "/Asset/Specular/Sand_Stone_Texture_specular.png"    // Bottom face
};

std::vector<Vertex> pyramidVerts(pyramidVertices, pyramidVertices + sizeof(pyramidVertices) / sizeof(Vertex));
std::vector<GLuint> pyramidInds(pyramidIndices, pyramidIndices + sizeof(pyramidIndices) / sizeof(GLuint));

Engine::Pyramid::Pyramid()
	: Mesh(ProjectDirectory "/Resource/Shader/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh.frag",
		pyramidVerts, pyramidInds, Core::Texture(), Core::Texture())
{
	Initialize();
}

Engine::Pyramid::Pyramid(const Core::Shader& shader)
	: Mesh(shader, pyramidVerts, pyramidInds, Core::Texture(), Core::Texture())
{
	Initialize();
}

void Engine::Pyramid::Render()
{
	shader.Activate();

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Pyramid::Update()
{
	shader.Activate();
	vao.Bind();

	for (size_t i = 0; i < 5; ++i)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuse.GetID(i));

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular.GetID(i));

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

	diffuse.LoadMultiple({ pyramidTexture.begin(), pyramidTexture.end() }, "diffuse", 0);
	specular.LoadMultiple({ pyramidSpecular.begin(), pyramidSpecular.end() }, "specular", 1);

	diffuse.SetUnit(shader, "diffuseSampler", 0);
	specular.SetUnit(shader, "specularSampler", 1);
}
