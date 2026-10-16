#pragma once

#ifndef ENGINE_CLOCK_H
#define ENGINE_CLOCK_H

#include <chrono>
#include <ctime>

namespace Engine
{
	class Clock
	{
	private:
		std::chrono::steady_clock::time_point start, finish;
		bool stop;
		
	public:
		Clock();
		~Clock() = default;

		void Stop();

		char* GetTime();
		std::chrono::milliseconds GetDurationInMilliseconds();
		std::chrono::seconds GetDurationInSeconds();
	};
}

#endif
