#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Graphics/Graphics.h"
#include "Graphics/Shader/Shader.h"

namespace Engine
{
	class Camera
	{
	public:
		glm::vec3 position;

	private:
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		glm::mat4 view;
		glm::mat4 projection;

		bool clicked = true;

		int width, height;

		float speed;
		const float walkSpeed = 10.0f;
		const float sprintSpeed = 2.5f;
		float sensitivity = 100.0f;

		float previousFrame;
		float deltaTime = 0.0f;
		double fps;

	public:
		Camera(glm::vec2 size, glm::vec3 position);
		virtual ~Camera();

		void UpdateMatrix(GLFWwindow* window, float fov, float nearPlane, float farPlane);
		void Matrix(const Core::Shader& shader, const std::string& uniform);
		void Inputs(GLFWwindow* window);	// Temporary input. Input class will be added later
		
	private:
		void Framerate();
	};
}

#endif
