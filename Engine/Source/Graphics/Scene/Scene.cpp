#include "Scene.h"

Engine::Scene::Scene(Core::App& app, const std::string& name)
	: app(app), name(name), selection()
{
}
