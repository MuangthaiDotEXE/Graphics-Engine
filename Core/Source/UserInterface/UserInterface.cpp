#include "UserInterface.h"

Core::UserInterface::UserInterface(Window* window, const std::string& title, const std::string& version, const std::string& graphicsAPI)
	: window(window), title(title), version(version), graphicsAPI(graphicsAPI)
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

	ImGui::Text("Window size: %.0fx%.0f", window->GetFramebufferSize().x, window->GetFramebufferSize().y);
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	ImGui::Text("FPS: %.1f", io.Framerate);
	ImGui::Text("Monitor sync: %s", window->GetMonitorSync() ? "On" : "Off");
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	ImGui::Text("Miscellaneous");
	ImGui::Text("Wireframe mode");
	ImGui::SameLine(0, 10);
	if (ImGui::Button(wireframeMode ? "Off" : "On"))
	{
		wireframeMode = !wireframeMode;

		if (wireframeMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	ImGui::Text("Button");
	ImGui::SameLine(0, 10);
	if (ImGui::Button("Button"))
	{
		std::print(stdout, "\033[0m[Debug] Button pressed!\033[0m\n");
	}
	ImGui::End();
}

void Core::UserInterface::DemoWindow()
{
	ImGui::ShowDemoWindow();
}
