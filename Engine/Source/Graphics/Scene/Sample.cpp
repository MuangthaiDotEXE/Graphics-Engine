#include "Sample.h"

static const std::array<std::string, 6> prototypeTexture
{
	ProjectDirectory "/Asset/Texture/Prototype_Texture.png",    // Front face
	ProjectDirectory "/Asset/Texture/Prototype_Texture.png",    // Right face
	ProjectDirectory "/Asset/Texture/Prototype_Texture.png",    // Back face
	ProjectDirectory "/Asset/Texture/Prototype_Texture.png",    // Left face
	ProjectDirectory "/Asset/Texture/Prototype_Texture.png",    // Bottom face
	ProjectDirectory "/Asset/Texture/Prototype_Texture.png"     // Top face
};

static const std::array<std::string, 6> prototypeSpecular
{
	ProjectDirectory "/Asset/Specular/Prototype_Texture_specular.png",    // Front face
	ProjectDirectory "/Asset/Specular/Prototype_Texture_specular.png",    // Right face
	ProjectDirectory "/Asset/Specular/Prototype_Texture_specular.png",    // Back face
	ProjectDirectory "/Asset/Specular/Prototype_Texture_specular.png",    // Left face
	ProjectDirectory "/Asset/Specular/Prototype_Texture_specular.png",    // Bottom face
	ProjectDirectory "/Asset/Specular/Prototype_Texture_specular.png"     // Top face
};
static const std::array<std::string, 6> cubeTexture
{
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png",    // Front face
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png",    // Right face
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png",    // Back face
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png",    // Left face
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png",    // Bottom face
	ProjectDirectory "/Asset/Texture/Red_Brick_Texture.png"     // Top face
};

static const std::array<std::string, 6> cubeSpecular
{
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png",    // Front face
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png",    // Right face
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png",    // Back face
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png",    // Left face
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png",    // Bottom face
	ProjectDirectory "/Asset/Specular/Red_Brick_Texture_specular.png"     // Top face
};

static const std::array<std::string, 5> pyramidTexture
{
	ProjectDirectory "/Asset/Texture/Yellow_Brick_Texture.png",    // Front face
	ProjectDirectory "/Asset/Texture/Yellow_Brick_Texture.png",    // Right face
	ProjectDirectory "/Asset/Texture/Yellow_Brick_Texture.png",    // Back face
	ProjectDirectory "/Asset/Texture/Yellow_Brick_Texture.png",    // Left face
	ProjectDirectory "/Asset/Texture/Yellow_Brick_Texture.png"     // Bottom face
};

static const std::array<std::string, 5> pyramidSpecular
{
	ProjectDirectory "/Asset/Specular/Yellow_Brick_Texture_specular.png",    // Front face
	ProjectDirectory "/Asset/Specular/Yellow_Brick_Texture_specular.png",    // Right face
	ProjectDirectory "/Asset/Specular/Yellow_Brick_Texture_specular.png",    // Back face
	ProjectDirectory "/Asset/Specular/Yellow_Brick_Texture_specular.png",    // Left face
	ProjectDirectory "/Asset/Specular/Yellow_Brick_Texture_specular.png"     // Bottom face
};

static const std::string sphereTexture = ProjectDirectory "/Asset/Texture/Earth_Color_Map.png";
static const std::string sphereSpecular = ProjectDirectory "/Asset/Specular/Earth_Bump_Map.png";

static const std::string planeTexture = ProjectDirectory "/Asset/Texture/Green_Brick_Texture.png";
static const std::string planeSpecular = ProjectDirectory "/Asset/Specular/Green_Brick_Texture_specular.png";

static const std::string quadTexture = ProjectDirectory "/Asset/Texture/Blue_Brick_Texture.png";
static const std::string quadSpecular = ProjectDirectory "/Asset/Specular/Blue_Brick_Texture_specular.png";

static const std::string triangleTexture = ProjectDirectory "/Asset/Texture/Purple_Brick_Texture.png";
static const std::string triangleSpecular = ProjectDirectory "/Asset/Specular/Purple_Brick_Texture_specular.png";

static const std::array<std::string, 6> skyCubemap
{
	ProjectDirectory "/Asset/Cubemap/Right.png",     // Right face
	ProjectDirectory "/Asset/Cubemap/Left.png",      // Left face
	ProjectDirectory "/Asset/Cubemap/Top.png",       // Top face
	ProjectDirectory "/Asset/Cubemap/Bottom.png",    // Bottom face
	ProjectDirectory "/Asset/Cubemap/Front.png",     // Front face
	ProjectDirectory "/Asset/Cubemap/Back.png"       // Back face
};

Engine::Sample::Sample(Core::App& app)
	: Scene(app), 
	skyShader(ProjectDirectory "/Resource/Shader/Sky/Sky.vert", ProjectDirectory "/Resource/Shader/Sky/Sky.frag"),
	sky(skyShader, std::vector<std::string>(skyCubemap.begin(), skyCubemap.end())),
	camera(app.window->GetWindow(), Camera::ProjectionMode::PERSPECTIVE, Camera::RotationMode::EULER, glm::vec3(8.75f, 8.75f, 8.75f), 70.0f, 0.001f, 1000.0f),
	grid(camera.GetNearPlane(), camera.GetFarPlane()), 
	objects(), 
	lights(), 
	meshShader(ProjectDirectory "/Resource/Shader/Mesh/Mesh.vert", ProjectDirectory "/Resource/Shader/Mesh/Mesh.frag"),
	fbo(app.window->GetFramebufferSize())
{
	auto prototype = std::make_unique<Cube>(meshShader, std::vector<std::string>(prototypeTexture.begin(), prototypeTexture.end()), std::vector<std::string>(prototypeSpecular.begin(), prototypeSpecular.end()));
	prototype->name = "Prototype";
	prototype->transform.position = glm::vec3(-5.0f, 1.0f, 5.0f);
	objects.emplace_back(std::move(prototype));

	auto cube = std::make_unique<Cube>(meshShader, std::vector<std::string>(cubeTexture.begin(), cubeTexture.end()), std::vector<std::string>(cubeSpecular.begin(), cubeSpecular.end()));
	cube->name = "Cube";
	cube->transform.position = glm::vec3(-5.0f, 1.0f, 0.0f);
	objects.emplace_back(std::move(cube));

	auto pyramid = std::make_unique<Pyramid>(meshShader, std::vector<std::string>(pyramidTexture.begin(), pyramidTexture.end()), std::vector<std::string>(pyramidSpecular.begin(), pyramidSpecular.end()));
	pyramid->name = "Pyramid";
	pyramid->transform.position = glm::vec3(0.0f, 1.0f, -5.0f);
	objects.emplace_back(std::move(pyramid));

	auto sphere = std::make_unique<Sphere>(meshShader, std::vector<std::string>{ sphereTexture }, std::vector<std::string>{ sphereSpecular });
	sphere->name = "Sphere";
	sphere->transform.position = glm::vec3(0.0f, 1.0f, 0.0f);
	objects.emplace_back(std::move(sphere));

	auto plane = std::make_unique<Plane>(meshShader, std::vector<std::string>{ planeTexture }, std::vector<std::string>{ planeSpecular });
	plane->name = "Plane";
	plane->transform.position = glm::vec3(5.0f, 1.0f, 0.0f);
	objects.emplace_back(std::move(plane));

	auto quad = std::make_unique<Quad>(meshShader, std::vector<std::string>{ quadTexture }, std::vector<std::string>{ quadSpecular });
	quad->name = "Quad";
	quad->transform.position = glm::vec3(5.0f, 1.0f, -5.0f);
	objects.emplace_back(std::move(quad));

	auto triangle = std::make_unique<Triangle>(meshShader, std::vector<std::string>{ triangleTexture }, std::vector<std::string>{triangleSpecular });
	triangle->name = "Triangle";
	triangle->transform.position = glm::vec3(-5.0f, 1.0f, -5.0f);
	objects.emplace_back(std::move(triangle));

	auto floor = std::make_unique<Plane>(meshShader);
	floor->name = "Floor";
	floor->transform.scale = glm::vec3(10.0f, 10.0f, 10.0f);
	objects.emplace_back(std::move(floor));

	auto light = std::make_unique<Light>();
	light->name = "Light";
	light->type = "Point light";
	light->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	light->transform.position = glm::vec3(0.0f, 3.5f, 0.0f);
	light->transform.scale = glm::vec3(0.25f);
	lights.emplace_back(std::move(light));
}

Engine::Sample::~Sample()
{
}

void Engine::Sample::Render()
{
	sky.shader.Activate();
	glUniform1i(glGetUniformLocation(sky.shader.programID, "skySampler"), 0);
	sky.Render();

	glm::vec4 lightColor = glm::vec4(0.0f);
	glm::vec3 lightPosition = glm::vec3(0.0f);

	for (auto& light : lights)
	{
		light->shader.Activate();

		glUniform4f(glGetUniformLocation(light->shader.programID, "color"), light->color.r, light->color.g, light->color.b, light->color.w);

		lightColor = light->color;
		lightPosition = light->transform.position;

		light->Render();
	}

	for (auto& mesh : objects)
	{
		mesh->shader.Activate();
		
		glUniform4f(glGetUniformLocation(mesh->shader.programID, "lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.w);
		glUniform3f(glGetUniformLocation(mesh->shader.programID, "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
		glUniform1f(glGetUniformLocation(mesh->shader.programID, "nearPlane"), camera.GetNearPlane());
		glUniform1f(glGetUniformLocation(mesh->shader.programID, "farPlane"), camera.GetFarPlane());

		mesh->Render();
	}

	grid.Render();
}

void Engine::Sample::Update()
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

	//glm::vec2 windowSize = app.window->GetFramebufferSize();
	//fbo.Resize(windowSize);

	//fbo.Bind();

	camera.Input();
	camera.UpdateMatrix(70.0f, 0.001f, 1000.0f, 2.5f);

	for (auto& light : lights)
	{
		light->shader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(light->shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(light->transform.GetMatrix()));
		camera.Matrix(light->shader, "cameraMatrix");

		light->Update();
	}
	
	for (auto& mesh : objects)
	{
		mesh->shader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(mesh->shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(mesh->transform.GetMatrix()));
		glUniform3f(glGetUniformLocation(mesh->shader.programID, "cameraPosition"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		camera.Matrix(mesh->shader, "cameraMatrix");

		mesh->Update();
	}

	grid.view = camera.GetView();
	grid.projection = camera.GetProjection();
	grid.nearPlane = camera.GetNearPlane();
	grid.farPlane = camera.GetFarPlane();
	grid.Update();

	//fbo.Unbind();
}

Engine::Camera Engine::Sample::GetCamera() const
{
	return camera;
}

GLuint Engine::Sample::GetViewportTexture() const
{
	return fbo.GetColorTexture();
}

glm::vec2 Engine::Sample::GetViewportSize() const
{
	return fbo.GetSize();
}
