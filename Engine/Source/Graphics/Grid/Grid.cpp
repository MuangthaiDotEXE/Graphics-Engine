#include "Grid.h"

Engine::Grid::Grid()
	: shader(ProjectDirectory "/Resource/Shader/Grid.vert", ProjectDirectory "/Resource/Shader/Grid.frag")
{
}

Engine::Grid::~Grid()
{
}

void Engine::Grid::Render()
{
	shader.Activate();
}

void Engine::Grid::Update()
{
	shader.Activate();
}
