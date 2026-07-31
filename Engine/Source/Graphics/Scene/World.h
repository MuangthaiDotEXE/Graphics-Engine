#pragma once

#ifndef WORLD_H
#define WORLD_H

#include "App.h"

#include "Scene.h"

namespace Engine
{
	class World : public Scene
	{
	public:
		World(Core::App& app);
		virtual ~World() = default;

		void Render() override;
		void Update() override;
	};
}

#endif
