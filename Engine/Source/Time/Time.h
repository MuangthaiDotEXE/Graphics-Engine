#pragma once

#ifndef ENGINE_TIME_H
#define ENGINE_TIME_H

namespace Engine
{
	class Time
	{
	public:
		float deltaTime;

	public:
		Time();
		virtual ~Time() = default;

		void UpdateDeltaTime();
	};
}

#endif
