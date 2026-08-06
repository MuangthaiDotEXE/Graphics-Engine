#include "Camera.h"

Engine::Camera::Camera(GLFWwindow* window, ProjectionMode projectionMode, RotationMode rotationMode, glm::vec3 position)
	: window(window), projectionMode(projectionMode), rotationMode(rotationMode), position(position)
{
	if (rotationMode == RotationMode::QUATERNION)
	{
		std::print(stdout, "\033[33m[Warn] Quaternion rotation is currently not working properly. Please use Euler rotation if possible (GLM math library)\033[0m\n");
	}

	if (glm::length(position) < 0.0001f)
	{
		front = glm::vec3(0.0f, 0.0f, -1.0f);

		pitch = 0.0f;
		yaw = -90.0f;

		if (rotationMode == RotationMode::QUATERNION)
		{
			rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			yaw = 0.0f;
		}
	}
	else
	{
		front = glm::normalize(-position);
		pitch = glm::degrees(glm::asin(front.y));

		if (rotationMode == RotationMode::EULER)
		{
			yaw = glm::degrees(glm::atan(front.z, front.x));
		}
		else if (rotationMode == RotationMode::QUATERNION)
		{
			yaw = glm::degrees(glm::atan(-front.x, -front.z));

			glm::quat quaternionYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::quat quaternionPitch = glm::angleAxis(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));

			rotation = glm::normalize(quaternionYaw * quaternionPitch);
			front = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
		}
	}
}

Engine::Camera::~Camera()
{
}

void Engine::Camera::UpdateMatrix(float fov, float nearPlane, float farPlane, float orthoZoomSize = 10.0f)
{
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);

	glfwGetFramebufferSize(window, &width, &height);
	if (width == 0 || height == 0)
	{
		return;
	}

	float aspect = (float)width / (float)height;

	if (rotationMode == RotationMode::EULER)
	{
		view = glm::lookAt(position, position + front, up);
	}
	else
	{
		view = glm::mat4_cast(glm::conjugate(rotation)) * glm::translate(glm::mat4(1.0f), -position);
	}
	if (projectionMode == ProjectionMode::PERSPECTIVE)
	{
		projection = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
	}
	else
	{
		float halfWidth = orthoZoomSize * aspect;
		float halfHeight = orthoZoomSize;

		projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane);
	}

	cameraMatrix = projection * view;
}

void Engine::Camera::Matrix(const Core::Shader& shader, const std::string& uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.programID, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Engine::Camera::Input()
{
	Framerate();
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = walkSpeed * deltaTime * speedMultiplier;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		speed = walkSpeed * deltaTime * slowMultiplier;
	}
	else
	{
		speed = walkSpeed * deltaTime;
	}

	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		/* Keyboard */
		{
			glm::vec3 moveDirection(0.0f);
			glm::vec3 normalizeRight = glm::normalize(glm::cross(front, up));

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				moveDirection += front;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				moveDirection -= normalizeRight;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				moveDirection -= front;
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				moveDirection += normalizeRight;
			}
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			{
				moveDirection += up;
			}
			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			{
				moveDirection -= up;
			}

			if (glm::length(moveDirection) > 0.0001f)
			{
				position += speed * glm::normalize(moveDirection);
			}
		}
	
		/* Mouse cursor */
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

			if (rotationMode == RotationMode::EULER)
			{
				pitch -= rotateX;
				yaw += rotateY;

				pitch = glm::clamp(pitch, -89.999f, 89.999f);

				front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
				front.y = glm::sin(glm::radians(pitch));
				front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
				front = glm::normalize(front);
			}
			else if (rotationMode == RotationMode::QUATERNION)
			{
				pitch -= rotateX;
				yaw -= rotateY;

				pitch = glm::clamp(pitch, -90.0f, 90.0f);

				glm::quat quaternionYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
				glm::quat quaternionPitch = glm::angleAxis(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));

				rotation = glm::normalize(quaternionYaw * quaternionPitch);
				front = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
			}

			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		clicked = true;
	}
}

glm::vec3 Engine::Camera::GetPosition() const
{
	return position;
}

glm::mat4 Engine::Camera::GetView() const
{
	return view;
}

glm::mat4 Engine::Camera::GetProjection() const
{
	return projection;
}

void Engine::Camera::Framerate()
{
	double currentFrame = glfwGetTime();

	deltaTime = currentFrame - previousFrame;
	previousFrame = currentFrame;

	fps = 1.0f / deltaTime;
}
