#include "Hierarchy.h"

Engine::UserInterface::Hierarchy::Hierarchy(Core::Window* window)
	: UserInterface(window, "Hierarchy")
{
}

Engine::UserInterface::Hierarchy::~Hierarchy()
{
}

void Engine::UserInterface::Hierarchy::Render()
{
}

void Engine::UserInterface::Hierarchy::Update()
{
	HierarchyWindow();
}

void Engine::UserInterface::Hierarchy::HierarchyWindow()
{
	ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("%s scene", "Sample");
	ImGui::Text("> %s", "Object");

	ImGui::End();
}
