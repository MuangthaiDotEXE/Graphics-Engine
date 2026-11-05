#include "Default.h"

namespace
{
	constexpr float FPS_GREAT_TRESHOLD = 36.0f;
	constexpr float FPS_OK_TRESHOLD = 24.0f;

	constexpr ImVec4 FPS_COLOR_GREAT = ImVec4(0.20f, 0.90f, 0.20f, 1.00f);
	constexpr ImVec4 FPS_COLOR_OK = ImVec4(1.00f, 0.85f, 0.10f, 1.00f);
	constexpr ImVec4 FPS_COLOR_BAD = ImVec4(0.95f, 0.20f, 0.20f, 1.00f);
	constexpr ImVec4 FPS_COLOR_FALLBACK = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

	ImVec4 GetFPSColor(float fps)
	{
		if (!(fps > 0.0f))
		{
			return FPS_COLOR_FALLBACK;
		}
		
		if (fps >= FPS_GREAT_TRESHOLD)
		{
			return FPS_COLOR_GREAT;
		}
		if (fps >= FPS_OK_TRESHOLD)
		{
			return FPS_COLOR_OK;
		}

		return FPS_COLOR_BAD;
	}

	ImVec4 GetMonitorSyncColor(bool vSync)
	{
		if (vSync)
		{
			return ImVec4(0.20f, 0.90f, 0.20f, 1.00f);
		}

		return ImVec4(0.95f, 0.20f, 0.20f, 1.00f);
	}
}

Engine::UserInterface::Default::Default(
	Core::Window* window, 
	const std::string& title, 
	const std::string& version, 
	const std::string& graphicsAPI,
	const glm::vec3& skyColor
)
	: UserInterface(window, "Default"),
	title(title),
	version(version),
	skyColor(skyColor),
	currentSkyColor(skyColor),
	graphicsAPI(graphicsAPI),
	vSync(window->GetMonitorSync())
{
}

Engine::UserInterface::Default::~Default()
{
}

void Engine::UserInterface::Default::Render()
{
}

void Engine::UserInterface::Default::Update()
{
	//DockSpace();
	DefaultWindow();
}

void Engine::UserInterface::Default::SetCameraPosition(glm::vec3 position)
{
	cameraPosition = position;
}

void Engine::UserInterface::Default::DefaultWindow()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui::Begin("Default", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("%s %s", title.c_str(), version.c_str());
	ImGui::Text("Graphics API: %s API", graphicsAPI.c_str());
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	ImGui::Text("Window size: %.0fx%.0f", window->GetWindowSize().x, window->GetWindowSize().y);
	ImGui::Text("Framebuffer size: %.0fx%.0f", window->GetFramebufferSize().x, window->GetFramebufferSize().y);
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	const float fps = Engine::Time::FPS();
	ImGui::TextUnformatted("FPS: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(GetFPSColor(fps), "%.2f", fps);
	ImGui::SameLine(0, 0);
	ImGui::Text(" (%.2f ms)", Time::FrameTimeMilliseconds());
	ImGui::TextUnformatted("Monitor sync (V-Sync): ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(GetMonitorSyncColor(vSync), "%s", vSync ? "Enabled" : "Disabled");
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	/* Miscellaneous */
	{
		ImGui::Text(" -- Miscellaneous -- ");

		//ImGui::Text("Position: %.3f, %.3f, %.3f", cameraPosition.x, cameraPosition.y, cameraPosition.z);

		ImGui::Text("Sky color");
		ImGui::ColorEdit3("##skyColor", glm::value_ptr(skyColor));
		glClearColor(skyColor.r, skyColor.g, skyColor.b, 1.0f);
		if (currentSkyColor != skyColor)
		{
			Core::Log::Debug("User interface", std::format("Sky color (RGB): {}, {}, {}", skyColor.r * 255, skyColor.g * 255, skyColor.b * 255));
			currentSkyColor = skyColor;
		}

		ImGui::Text("Monitor sync");
		ImGui::SameLine(0, 10);
		if (ImGui::Button(vSync ? "Disable##vSync" : "Enable##vSync"))
		{
			vSync = !vSync;

			if (vSync)
			{
				glfwSwapInterval(true);
			}
			else
			{
				glfwSwapInterval(false);
			}

			Core::Log::Debug("User interface", std::format("Monitor sync (V-Sync): {}", vSync ? "Enable" : "Disable"));
		}

		ImGui::Text("Wireframe");
		ImGui::SameLine(0, 10);
		if (ImGui::Button(wireframe ? "Disable##wireframe" : "Enable##wireframe"))
		{
			wireframe = !wireframe;

			if (wireframe)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			Core::Log::Debug("User interface", std::format("Wireframe: {}", wireframe ? "Enabled" : "Disabled"));
		}

		ImGui::Text("Text");
		ImGui::SameLine(0, 10);
		if (ImGui::Button("Button"))
		{
			Core::Log::Debug("User interface", "Button pressed!");
		}
	}

	ImGui::End();
}

void Engine::UserInterface::Default::ViewportWindow(GLuint textureID, glm::vec2 size)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Viewport");

	ImVec2 viewportSize = ImGui::GetContentRegionAvail();

	float aspectRatio = (float)viewportSize.x / (float)viewportSize.y;

	ImGui::Image((ImTextureID)(uintptr_t)textureID, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
	ImGui::PopStyleVar();
}

void Engine::UserInterface::Default::DockSpace()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGuiWindowFlags dockFlags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("DockSpace", nullptr, dockFlags);
	ImGui::PopStyleVar(3);

	ImGuiID dockID = ImGui::GetID("MainDockSpace");
	ImGui::DockSpace(dockID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

	ImGui::End();
}

void Engine::UserInterface::Default::DeveloperWindow()
{
	ImGui::ShowAboutWindow();
	ImGui::ShowDemoWindow();
	ImGui::ShowDebugLogWindow();
	ImGui::ShowIDStackToolWindow();
	ImGui::ShowUserGuide();
}
