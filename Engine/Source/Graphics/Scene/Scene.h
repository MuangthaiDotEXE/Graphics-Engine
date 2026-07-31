#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <GLFW/glfw3.h>

#include "App.h"

namespace Engine
{
	class Scene
	{
	protected:
		Core::App& app;

	public:
		Scene(Core::App& app);
		virtual ~Scene() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;
	};
}

#endif
