#include "Mesh.h"

glm::mat4 Engine::Mesh::MeshTransform::GetMatrix() const
{
	glm::mat4 matrix = glm::mat4(1.0f);

	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, scale);

	return matrix;
}

Engine::Mesh::Mesh(const std::string& vertexShader, const std::string& fragmentShader, std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const Core::Texture& diffuse, const Core::Texture& specular)
	: shader(vertexShader, fragmentShader), vao(), vbo(vertices), ebo(indices), diffuse(diffuse), specular(specular)
{
}

Engine::Mesh::Mesh(const Core::Shader& shader, std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const Core::Texture& diffuse, const Core::Texture& specular)
	: shader(shader), vao(), vbo(vertices), ebo(indices), diffuse(diffuse), specular(specular)
{
}
