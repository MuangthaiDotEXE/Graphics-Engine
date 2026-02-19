#include "Mesh.h"

Engine::Mesh::Mesh(const std::string& vertexShader, const std::string& fragmentShader, std::vector<vertex>& vertices, std::vector<GLuint>& indices)
	: shader(vertexShader, fragmentShader), vao(), vbo(vertices), ebo(indices)
{
}
