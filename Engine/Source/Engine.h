#ifndef ENGINE_H
#define ENGINE_H

#include "App.h"

#include "Graphics/Mesh.h"

namespace Engine
{
	class Engine
	{
	private:
		App::App app;

		Mesh mesh;

	public:
		Engine(const App::AppData& appData);
		virtual ~Engine();

		void Render();
		void Update();
	};
}

#endif
