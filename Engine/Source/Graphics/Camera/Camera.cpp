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

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	view = glm::lookAt(position, position + orientation, up);
	projection = glm::perspective(glm::radians(fov), (float)width / height, nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Engine::Camera::Matrix(const App::Shader& shader, const std::string& uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.programID, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Engine::Camera::Inputs(GLFWwindow* window)
{
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
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			position += speed * up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			position -= speed * up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			speed = sprintSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			speed = walkSpeed;
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

			glm::vec3 rotateOrientation = glm::rotate(orientation, glm::radians(-rotateX), glm::normalize(glm::cross(orientation, up)));

			if (glm::abs(glm::angle(rotateOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				orientation = rotateOrientation;
			}

			orientation = glm::rotate(orientation, glm::radians(-rotateY), up);

			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			clicked = true;
		}
	}
}
