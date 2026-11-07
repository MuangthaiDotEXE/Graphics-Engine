#pragma once

#ifndef ENGINE_SELECTION_H
#define ENGINE_SELECTION_H

#include <cmath>
#include <limits>
#include <vector>
#include <memory>
#include <algorithm>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Mesh/Mesh.h"

namespace Engine
{
	class Selection
	{
	public:
		enum struct ReclickMode
		{
			SELECTBEHIND,
			KEEPSELECTED
		};

		ReclickMode reclickMode = ReclickMode::SELECTBEHIND;
		glm::vec4 outlineColor = glm::vec4(1.00f, 0.55f, 0.00f, 1.00f);
		float dragTreshold = 4.0f;

	private:
		struct Ray
		{
			glm::vec3 origin;
			glm::vec3 direction;
		};

		Core::Shader outlineShader;
		GLuint vao = 0, vbo = 0, ebo = 0;

		Mesh* selected = nullptr;
		bool wasMouseDown = false;

		bool dragPending = false;
		bool dragging = false;
		Mesh* behindCandidate = nullptr;
		glm::vec2 dragStartMouse = glm::vec2(0.0f);
		glm::vec3 dragPlaneNormal = glm::vec3(0.0f);
		glm::vec3 dragPlanePoint = glm::vec3(0.0f);
		glm::vec3 dragOffset = glm::vec3(0.0f);

	public:
		Selection();
		Selection(const Selection&) = delete;
		Selection& operator=(const Selection&) = delete;
		virtual ~Selection();

		void Update(GLFWwindow* window,
			const glm::mat4& view,
			const glm::mat4& projection,
			const glm::vec2& viewportPosition,
			const glm::vec2& viewportSize,
			const std::vector<std::unique_ptr<Mesh>>& meshes,
			bool inputAllowed
		);
		void DrawOutline(Camera& camera);

		Mesh* Get() const;
		void Clear();

	private:
		static Ray CreateRay(const glm::vec2& local, const glm::vec2& viewportSize, const glm::mat4& view, const glm::mat4& projection);
		static bool IntersectPlane(const Ray& ray, const glm::vec3& planePoint, const glm::vec3& planeNormal, glm::vec3& outPoint);
		static bool IntersectLocalBox(const Mesh& mesh, const Ray& worldRay, float& outT);
	};
}

#endif
