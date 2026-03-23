#include "UserInterface.h"

Core::UserInterface::UserInterface(std::string title, std::string version, std::string graphicsAPI, GLFWwindow* window)
	: title(title), version(version), graphicsAPI(graphicsAPI), window(window)
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

	ImGui_ImplGlfw_InitForOpenGL(window, true);
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

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	ImGui::Text("Window size: %ix%i", width, height);
	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	ImGui::Text("FPS: %.1f", io.Framerate);
	ImGui::End();
}

void Core::UserInterface::DemoWindow()
{
	ImGui::ShowDemoWindow();
}
