#include "Mesh.h"

glm::mat4 Engine::Mesh::Transform::GetMatrix() const
{
	glm::mat4 matrix = glm::mat4(1.0f);

	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, scale);

	return matrix;
}

Engine::Mesh::Mesh(const std::string& vertexShader, 
	const std::string& fragmentShader, 
	std::vector<Vertex>& vertices, 
	std::vector<GLuint>& indices, 
	std::optional<std::vector<std::string>> diffuse,
	std::optional<std::vector<std::string>> specular
)
	: shader(vertexShader, fragmentShader), 
	vao(), 
	vbo(vertices), 
	ebo(indices), 
	diffuse(std::move(diffuse), "diffuse", 0),
	specular(std::move(specular), "specular", 1)
{
}

Engine::Mesh::Mesh(const Core::Shader& shader, 
	std::vector<Vertex>& vertices, 
	std::vector<GLuint>& indices, 
	std::optional<std::vector<std::string>> diffuse,
	std::optional<std::vector<std::string>> specular
)
	: shader(shader), 
	vao(), 
	vbo(vertices), 
	ebo(indices), 
	diffuse(std::move(diffuse), "diffuse", 0),
	specular(std::move(specular), "specular", 1)
{
}
