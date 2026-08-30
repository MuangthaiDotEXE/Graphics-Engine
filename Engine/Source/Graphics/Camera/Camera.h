#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Graphics/Graphics.h"
#include "Graphics/Shader/Shader.h"

namespace Engine
{
	class Camera
	{
	private:
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 position;

		glm::mat4 cameraMatrix = glm::mat4(1.0f);
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

		float pitch = 0.0f;
		float yaw = -90.0f;

		glm::mat4 view;
		glm::mat4 projection;

		float fov, nearPlane, farPlane;
		float orthographicZoomSize = 10.0f;

		bool clicked = true;

		int width, height;
		GLFWwindow* window;

		float speed;
		const float walkSpeed = 10.0f;
		const float speedMultiplier = 2.5f;
		const float slowMultiplier = 0.4f;
		float sensitivity = 100.0f;

		double previousFrame;
		double deltaTime = 0.0f;
		double fps;

	public:
		enum struct VectorAxis { ORIENTATION, FRONT, RIGHT, UP };
		enum struct ProjectionMode { PERSPECTIVE, ORTHOGRAPHIC };
		enum struct RotationMode { EULER, QUATERNION };

		ProjectionMode projectionMode;
		RotationMode rotationMode;

	public:
		Camera(GLFWwindow* window, 
			ProjectionMode projectionMode, 
			RotationMode rotationMode, 
			glm::vec3 position,
			float fov, 
			float nearPlane, 
			float farPlane,
			float orthographicZoomSize = 10.0f
		);
		virtual ~Camera();

		void UpdateMatrix(float fov, float nearPlane, float farPlane, float orthographicZoomSize = 10.0f);
		void Matrix(const Core::Shader& shader, const std::string& uniform);
		void Input();	// Temporary input. Input class will be added in future update

		float GetFieldOfView() const;
		float GetNearPlane() const;
		float GetFarPlane() const;
		glm::vec3 GetVectorAxis(VectorAxis vectorAxis) const;
		glm::vec3 GetPosition() const;
		glm::mat4 GetView() const;
		glm::mat4 GetProjection() const;
		glm::quat GetQuaternionRotation() const;
		ProjectionMode GetProjectionMode() const;
		RotationMode GetRotationMode() const;
		float GetOrthographicZoomSize() const;
		
	private:
		void Framerate();
	};
}

#endif
