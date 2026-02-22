#include "Mesh.h"

Engine::Mesh::Mesh(const std::string& vertexShader, const std::string& fragmentShader, std::vector<vertex>& vertices, std::vector<GLuint>& indices, const Core::Texture& texture, const Core::Texture specular)
	: shader(vertexShader, fragmentShader), vao(), vbo(vertices), ebo(indices), texture(texture), specular(specular)
{
}
