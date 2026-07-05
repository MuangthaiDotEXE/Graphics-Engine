#include "UserInterface.h"

Core::UserInterface::UserInterface(Window* window, const std::string& title, const std::string& version, const std::string& graphicsAPI, const glm::vec3& skyColor)
	: window(window), title(title), version(version), skyColor(skyColor), graphicsAPI(graphicsAPI), vSync(window->GetMonitorSync())
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	float mainScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(mainScale);
	style.FontScaleDpi = mainScale;

	ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

Core::UserInterface::~UserInterface()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Core::UserInterface::Render()
{
}

void Core::UserInterface::BeginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Core::UserInterface::Update()
{
	//DockSpace();
	DebugWindow();
}

void Core::UserInterface::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* context = glfwGetCurrentContext();

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(context);
	}
}

void Core::UserInterface::DebugWindow()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("%s %s", title.c_str(), version.c_str());
	ImGui::Text("Graphics API: %s API", graphicsAPI.c_str());
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	ImGui::Text("Window size: %.0fx%.0f", window->GetWindowSize().x, window->GetWindowSize().y);
	ImGui::Text("Framebuffer size: %.0fx%.0f", window->GetFramebufferSize().x, window->GetFramebufferSize().y);
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	ImGui::Text("FPS: %.2f", io.Framerate);
	ImGui::Text("Monitor sync (V-Sync): %s", vSync ? "Enabled" : "Disabled");
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	/* Miscellaneous */
	{
		ImGui::Text(" -- Miscellaneous -- ");

		ImGui::Text("Position: %.3f, %.3f, %.3f", coordinate.x, coordinate.y, coordinate.z);

		ImGui::Text("Sky color");
		ImGui::ColorEdit3("", glm::value_ptr(skyColor));
		glClearColor(skyColor.r, skyColor.g, skyColor.b, 1.0f);
		
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

			std::print(stdout, "\033[32m[Debug] Monitor sync (V-Sync): {}\033[0m\n", vSync ? "Enable" : "Disable");
		}

		static bool wireframe = false;
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

			std::print(stdout, "\033[32m[Debug] Wireframe: {}\033[0m\n", wireframe ? "Enabled" : "Disabled");
		}
		
		ImGui::Text("Text");
		ImGui::SameLine(0, 10);
		if (ImGui::Button("Button"))
		{
			std::print(stdout, "\033[32m[Debug] Button pressed!\033[0m\n");
		}
	}
	ImGui::End();
}

void Core::UserInterface::ViewportWindow(GLuint textureID, glm::vec2 size)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Viewport");

	ImVec2 viewportSize = ImGui::GetContentRegionAvail();

	float aspectRatio = (float)viewportSize.x / (float)viewportSize.y;

	ImGui::Image((ImTextureID)(uintptr_t)textureID, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
	ImGui::PopStyleVar();
}

void Core::UserInterface::DockSpace()
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

void Core::UserInterface::DevWindow()
{
	ImGui::ShowAboutWindow();
	ImGui::ShowDemoWindow();
	ImGui::ShowDebugLogWindow();
	ImGui::ShowIDStackToolWindow();
	ImGui::ShowUserGuide();
}
