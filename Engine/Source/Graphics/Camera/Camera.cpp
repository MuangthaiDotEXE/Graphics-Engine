#include "Camera.h"

Engine::Camera::Camera(glm::vec2 size, glm::vec3 position)
	: width(size.x), height(size.y), position(position)
{
}

Engine::Camera::~Camera()
{
}

void Engine::Camera::UpdateMatrix(GLFWwindow* window, float fov, float nearPlane, float farPlane)
{
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);

	glfwGetFramebufferSize(window, &width, &height);

	if (width == 0 || height == 0) return;

	view = glm::lookAt(position, position + orientation, up);
	projection = glm::perspective(glm::radians(fov), (float)width / (float)height, nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Engine::Camera::Matrix(const Core::Shader& shader, const std::string& uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.programID, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Engine::Camera::Framerate()
{
	double currentFrame = glfwGetTime();

	deltaTime = currentFrame - previousFrame;
	previousFrame = currentFrame;

	fps = 1.0f / deltaTime;
}

void Engine::Camera::Inputs(GLFWwindow* window)
{
	Framerate();
	speed = walkSpeed * deltaTime * (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? sprintSpeed : 1.0f);

	// Keyboard
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			position += speed * orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			position -= speed * glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			position -= speed * orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			position += speed * glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			position += speed * up;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			position -= speed * up;
		}
	}

	// Mouse
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (clicked)
			{
				glfwSetCursorPos(window, (width / 2), (height / 2));
				clicked = false;
			}

			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotateX = sensitivity * (float)(mouseY - (height / 2)) / height;
			float rotateY = sensitivity * (float)(mouseX - (width / 2)) / width;

			pitch -= rotateX;
			yaw += rotateY;

			pitch = glm::clamp(pitch, -89.999f, 89.999f);

			orientation.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
			orientation.y = glm::sin(glm::radians(pitch));
			orientation.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
			orientation = glm::normalize(orientation);

			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			clicked = true;
		}
	}
}
