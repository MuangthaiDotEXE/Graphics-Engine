#pragma once

#ifndef MODEL_MESH_H
#define MODEL_MESH_H

#include "../Mesh/Mesh.h"

namespace Engine
{
	class ModelMesh : public Mesh
	{
	private:
		GLsizei indexCount;

	public:
		ModelMesh(const Core::Shader& shader,
			std::vector<Vertex>& vertices,
			std::vector<GLuint>& indices,
			std::optional<std::vector<std::string>> diffuse,
			std::optional<std::vector<std::string>> specular
		);

		void Render() override;
		void Update() override;

		void SetupMesh();
	};
}

#endif
