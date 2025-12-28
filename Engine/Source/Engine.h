#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

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
