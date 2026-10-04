#include "Space.h"

static const std::string earthTexture = ProjectDirectory "/Asset/Texture/Earth_Color_Map.png";
static const std::string earthSpecular = ProjectDirectory "/Asset/Specular/Earth_Bump_Map.png";

static const std::array<std::string, 6> spaceCubemap
{
	ProjectDirectory "/Asset/Cubemap/Space/Right.png",     // Right face
	ProjectDirectory "/Asset/Cubemap/Space/Left.png",      // Left face
	ProjectDirectory "/Asset/Cubemap/Space/Top.png",       // Top face
	ProjectDirectory "/Asset/Cubemap/Space/Bottom.png",    // Bottom face
	ProjectDirectory "/Asset/Cubemap/Space/Front.png",     // Front face
	ProjectDirectory "/Asset/Cubemap/Space/Back.png"       // Back face
};

Engine::Space::Space(Core::App& app)
	: Scene(app),
	spaceShader(ProjectDirectory "/Resource/Shader/Sky/Sky.vert", ProjectDirectory "/Resource/Shader/Sky/Sky.frag"),
	space(spaceShader, std::vector<std::string>(spaceCubemap.begin(), spaceCubemap.end())),
	camera(app.window->GetWindow(), Camera::ProjectionMode::PERSPECTIVE, Camera::RotationMode::EULER, glm::vec3(8.75f, 8.75f, 8.75f), 70.0f, 0.001f, 1000.0f),
	planetShader(ProjectDirectory "/Resource/Shader/Mesh/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh/Mesh.frag"),
	planets(),
	stars(),
	fbo(app.window->GetFramebufferSize())
{
	auto earth = std::make_unique<Sphere>(planetShader, std::vector<std::string>{ earthTexture }, std::vector<std::string>{ earthSpecular });
	earth->name = "Earth";
	earth->transform.position = glm::vec3(0.0f, 1.0f, 0.0f);
	planets.emplace_back(std::move(earth));

	auto sun = std::make_unique<Light>(true);
	sun->name = "Sun";
	sun->type = "Point light";
	sun->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	sun->transform.position = glm::vec3(-25.0f, 0.0f, 0.0f);
	sun->transform.scale = glm::vec3(5.0);
	stars.emplace_back(std::move(sun));
}

void Engine::Space::Render()
{
	space.shader.Activate();
	glUniform1i(glGetUniformLocation(space.shader.programID, "skySampler"), 0);
	space.Render();

	glm::vec4 starColor = glm::vec4(0.0f);
	glm::vec3 starPosition = glm::vec3(0.0f);

	for (auto& star : stars)
	{
		star->shader.Activate();

		glUniform4f(glGetUniformLocation(star->shader.programID, "color"), star->color.r, star->color.g, star->color.b, star->color.w);

		starColor = star->color;
		starPosition = star->transform.position;

		star->Render();
	}

	for (auto& planet : planets)
	{
		planet->shader.Activate();

		glUniform4f(glGetUniformLocation(planet->shader.programID, "lightColor"), starColor.r, starColor.g, starColor.b, starColor.w);
		glUniform3f(glGetUniformLocation(planet->shader.programID, "lightPosition"), starPosition.x, starPosition.y, starPosition.z);
		glUniform1f(glGetUniformLocation(planet->shader.programID, "nearPlane"), camera.GetNearPlane());
		glUniform1f(glGetUniformLocation(planet->shader.programID, "farPlane"), camera.GetFarPlane());

		planet->Render();
	}
}

void Engine::Space::Update()
{
	glDepthFunc(GL_LEQUAL);

	space.shader.Activate();

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

		glUniformMatrix4fv(glGetUniformLocation(space.shader.programID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(space.shader.programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	}

	space.Update();

	glDepthFunc(GL_LESS);

	//glm::vec2 windowSize = app.window->GetFramebufferSize();
	//fbo.Resize(windowSize);

	//fbo.Bind();

	camera.Input();
	camera.UpdateMatrix(70.0f, 0.001f, 1000.0f, 2.5f);

	for (auto& star : stars)
	{
		star->shader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(star->shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(star->transform.GetMatrix()));
		camera.Matrix(star->shader, "cameraMatrix");

		star->Update();
	}

	for (auto& planet : planets)
	{
		planet->shader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(planet->shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(planet->transform.GetMatrix()));
		glUniform3f(glGetUniformLocation(planet->shader.programID, "cameraPosition"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		camera.Matrix(planet->shader, "cameraMatrix");

		planet->Update();
	}

	//fbo.Unbind();
}

Engine::Camera Engine::Space::GetCamera() const
{
	return camera;
}

GLuint Engine::Space::GetViewportTexture() const
{
	return fbo.GetColorTexture();
}

glm::vec2 Engine::Space::GetViewportSize() const
{
	return fbo.GetSize();
}
