#pragma once

#ifndef MANAGER_H
#define MANAGER_H

#include "Log/Log.h"
#include "App.h"

namespace Manager
{
	class Manager
	{
	private:
		Core::App app;

	public:
		Manager(const Core::AppData& appData);
		virtual ~Manager();

		void Render();
		void Update();
	};
}

#endif
