#pragma once

#ifndef MANAGER_H
#define MANAGER_H

#include "Log/Log.h"
#include "App.h"

namespace Manager
{
	class Manager
	{
	public:
		Manager();
		virtual ~Manager();

		void Render();
		void Update();
	};
}

#endif
