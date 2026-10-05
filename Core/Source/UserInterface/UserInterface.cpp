#include "UserInterface.h"

Core::UserInterface::UserInterface::UserInterface(Window* window, 
	const std::string& title, 
	const std::string& version, 
	const std::string& graphicsAPI, 
	const glm::vec3& skyColor
)
	: window(window), 
	title(title), 
	version(version), 
	skyColor(skyColor), 
	graphicsAPI(graphicsAPI), 
	vSync(window->GetMonitorSync())
{
}

Core::UserInterface::UserInterface::~UserInterface()
{
}

void Core::UserInterface::UserInterface::Render()
{
}

void Core::UserInterface::UserInterface::BeginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Core::UserInterface::UserInterface::Update()
{
}

void Core::UserInterface::UserInterface::EndFrame()
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
