#include "World.h"

static const std::array<std::string, 6> skyCubemap
{
	ProjectDirectory "/Asset/Cubemap/Right.png",     // Right face
	ProjectDirectory "/Asset/Cubemap/Left.png",      // Left face
	ProjectDirectory "/Asset/Cubemap/Top.png",       // Top face
	ProjectDirectory "/Asset/Cubemap/Bottom.png",    // Bottom face
	ProjectDirectory "/Asset/Cubemap/Front.png",     // Front face
	ProjectDirectory "/Asset/Cubemap/Back.png"       // Back face
};

Engine::World::World(Core::App& app)
	: Scene(app),
	grid(),
	camera(app.window->GetWindow(), Camera::ProjectionMode::PERSPECTIVE, Camera::RotationMode::EULER, glm::vec3(8.75f, 8.75f, 8.75f), 70.0f, 0.001f, 1000.0f),
	sky(std::vector<std::string>(skyCubemap.begin(), skyCubemap.end()))
{
}

void Engine::World::Render()
{
	sky.shader.Activate();
	glUniform1i(glGetUniformLocation(sky.shader.programID, "skySampler"), 0);
	sky.Render();

	grid.Render();
}

void Engine::World::Update()
{
	glDepthFunc(GL_LEQUAL);

	sky.shader.Activate();

	int width, height;
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	glfwGetFramebufferSize(app.window->GetWindow(), &width, &height);
	if (width > 0 && height > 0)
	{
		float aspect = (float)width / height;

		if (camera.GetRotationMode() == Camera::RotationMode::EULER)
		{
			view = glm::mat4(glm::mat3(glm::lookAt(camera.GetPosition(), camera.GetPosition() + camera.GetVectorAxis(Camera::VectorAxis::FRONT), camera.GetVectorAxis(Camera::VectorAxis::UP))));
		}
		else
		{
			view = glm::mat4_cast(glm::conjugate(camera.GetQuaternionRotation())) * glm::translate(glm::mat4(1.0f), -camera.GetPosition());
		}

		if (camera.GetProjectionMode() == Camera::ProjectionMode::PERSPECTIVE)
		{
			projection = glm::perspective(glm::radians(camera.GetFieldOfView()), aspect, camera.GetNearPlane(), camera.GetFarPlane());
		}
		else
		{
			float halfWidth = camera.GetOrthographicZoomSize() * aspect;
			float halfHeight = camera.GetOrthographicZoomSize();

			projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, camera.GetNearPlane(), camera.GetFarPlane());
		}

		glUniformMatrix4fv(glGetUniformLocation(sky.shader.programID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(sky.shader.programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	}

	sky.Update();

	glDepthFunc(GL_LESS);

	camera.Input();
	camera.UpdateMatrix(70.0f, 0.001f, 1000.0f, 2.5f);

	grid.view = camera.GetView();
	grid.projection = camera.GetProjection();
	grid.nearPlane = camera.GetNearPlane();
	grid.farPlane = camera.GetFarPlane();
	grid.Update();
}

GLuint Engine::World::GetViewportTexture() const
{
	return GLuint();
}

glm::vec2 Engine::World::GetViewportSize() const
{
	return glm::vec2();
}
