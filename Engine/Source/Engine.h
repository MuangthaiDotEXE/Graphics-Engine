#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <glad/gl.h>

#include "App.h"

#include "Graphics/Mesh/Mesh.h"
#include "Graphics/Camera/Camera.h"

namespace Engine
{
	class Engine
	{
	private:
		App::App app;

		Mesh mesh;
		Camera camera;

	public:
		Engine(const App::AppData& appData);
		virtual ~Engine();

		void Render();
		void Update();
	};
}

#endif
