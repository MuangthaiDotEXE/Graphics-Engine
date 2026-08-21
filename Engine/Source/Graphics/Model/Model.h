#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <print>
#include <string>
#include <format>
#include <cstddef>
#include <vector>
#include <memory>
#include <optional>
#include <filesystem>
#include <stdexcept>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Mesh/Mesh.h"

namespace Engine
{
	class Model : public Mesh
	{
	private:
		struct SubMesh
		{
			bool hasDiffuse, hasSpecular;

			Core::Shader shader;
			Core::VAO vao;
			Core::VBO vbo;
			Core::EBO ebo;
			Core::Texture diffuse;
			Core::Texture specular;

			GLsizei indexCount;

			SubMesh(std::vector<Vertex>& vertices,
				std::vector<GLuint>& indices,
				std::optional<std::vector<std::string>> diffusePaths,
				std::optional<std::vector<std::string>> specularPaths,
				Core::Shader& shader
			);
			SubMesh(const SubMesh&) = delete;
			SubMesh& operator=(const SubMesh&) = delete;
		};

	private:
		std::vector<std::unique_ptr<SubMesh>> subMeshes;
		std::string directory;
		bool flipUVs;

	public:
		Model(const std::string& path, bool flipUVs = true);
		Model(const std::string& path, const Core::Shader& shader, bool flipUVs = false);
		virtual ~Model() = default;

		void Render() override;
		void Update() override;

		size_t GetSubMeshCount() const;

	private:
		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& parentTransform);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& nodeTransform);
		std::optional<std::vector<std::string>> LoadMaterialTextures(aiMaterial* material, aiTextureType type);

		static std::vector<Vertex>& DummyVertices();
		static std::vector<GLuint>& DummyIndices();
	};
}

#endif
