#include "Mesh.h"

GLfloat meshVertices[] =
{
	// positions		   // colors		   // textures    // normals
	-1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 1.0f,    0.0f,  0.0f,  1.0f,   // Front face top left vertex
	 1.0f,  1.0f,  1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,    0.0f,  0.0f,  1.0f,   // Front face top right vertex
	 1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 1.0f,   1.0f, 0.0f,    0.0f,  0.0f,  1.0f,   // Front face bottom right vertex
	-1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,    0.0f,  0.0f,  1.0f,   // Front face bottom left vertex
															   		 	   
	-1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,   // Right face top left vertex
	-1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 1.0f,   1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,   // Right face top right vertex
	-1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,   // Right face bottom right vertex
	-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,   // Right face bottom left vertex
															   		 
	 1.0f,  1.0f, -1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    0.0f,  0.0f, -1.0f,   // Back face top left vertex
	-1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,    0.0f,  0.0f, -1.0f,   // Back face top right vertex
	-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,    0.0f,  0.0f, -1.0f,   // Back face bottom right vertex
	 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,    0.0f,  0.0f, -1.0f,   // Back face bottom left vertex
															    	 
	 1.0f,  1.0f,  1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,    1.0f,  0.0f,  0.0f,   // Left face top left vertex
	 1.0f,  1.0f, -1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,    1.0f,  0.0f,  0.0f,   // Left face top right vertex
	 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,    1.0f,  0.0f,  0.0f,   // Left face bottom right vertex
	 1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,    1.0f,  0.0f,  0.0f,   // Left face bottom left vertex
															     	 	    
	-1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,    0.0f,  1.0f,  0.0f,   // Top face top left vertex
	 1.0f,  1.0f, -1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,    0.0f,  1.0f,  0.0f,   // Top face top right vertex
	 1.0f,  1.0f,  1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,    0.0f,  1.0f,  0.0f,   // Top face bottom right vertex
	-1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 0.0f,    0.0f,  1.0f,  0.0f,   // Top face bottom left vertex
															   			    
	-1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,    0.0f, -1.0f,  0.0f,   // Bottom face top left vertex
	 1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 1.0f,   1.0f, 1.0f,    0.0f, -1.0f,  0.0f,   // Bottom face top right vertex
	 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   // Bottom face bottom right vertex
	-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,    0.0f, -1.0f,  0.0f   // Bottom face bottom left vertex
};

GLuint meshIndices[] =
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

std::string textureImages[] =
{
	ProjectDirectory "/Asset/Texture/Brick_Texture.png",
	ProjectDirectory "/Asset/Texture/Brick_Texture.png",
	ProjectDirectory "/Asset/Texture/Brick_Texture.png",
	ProjectDirectory "/Asset/Texture/Brick_Texture.png",
	ProjectDirectory "/Asset/Texture/Brick_Texture.png",
	ProjectDirectory "/Asset/Texture/Brick_Texture.png"
};

std::string specularImages[] =
{
	ProjectDirectory "/Asset/Texture/Brick_Texture_specular.png",
	ProjectDirectory "/Asset/Texture/Brick_Texture_specular.png",
	ProjectDirectory "/Asset/Texture/Brick_Texture_specular.png",
	ProjectDirectory "/Asset/Texture/Brick_Texture_specular.png",
	ProjectDirectory "/Asset/Texture/Brick_Texture_specular.png",
	ProjectDirectory "/Asset/Texture/Brick_Texture_specular.png"
};

Engine::Mesh::Mesh()
	: shader(ProjectDirectory "/Resource/Shader/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh.frag"), 
	vao(), vbo(meshVertices, sizeof(meshVertices)), ebo(meshIndices, sizeof(meshIndices)), 
	texture(), specularMap(), 
	textures(texture.Initialize(textureImages, sizeof(textureImages) / sizeof(std::string), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE)), 
	specularMaps(specularMap.Initialize(specularImages, sizeof(specularImages) / sizeof(std::string), GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE))
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

	texture.textureUnit(shader, "textureSampler", 0);
	specularMap.textureUnit(shader, "specularMapSampler", 1);
}

Engine::Mesh::~Mesh()
{
}

void Engine::Mesh::Render()
{
	shader.Activate();

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Engine::Mesh::Update()
{
	shader.Activate();
	texture.Bind();
	specularMap.Bind();
	vao.Bind();

	for (size_t i = 0; i < sizeof(textureImages) / sizeof(std::string); i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glDrawElements(GL_TRIANGLES, sizeof(meshIndices) / sizeof(GLuint), GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(GLuint)));
	}
}
