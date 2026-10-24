#pragma once

#ifndef ENGINE_USERINTERFACE_HIERARCHY_H
#define ENGINE_USERINTERFACE_HIERARCHY_H

#include "Window/Window.h"
#include "UserInterface/UserInterface.h"

namespace Engine::UserInterface
{
	class Hierarchy : public Core::UserInterface::UserInterface
	{
	public:
		Hierarchy(Core::Window* window);
		virtual ~Hierarchy();
		
		void Render() override;
		void Update() override;

	private:
		void HierarchyWindow();
	};
}

#endif
