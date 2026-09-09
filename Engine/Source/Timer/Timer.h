#pragma once

#ifndef ENGINE_TIMER_H
#define ENGINE_TIMER_H

#include <chrono>

namespace Engine
{
	class Timer
	{
	private:
		std::chrono::steady_clock::time_point start, finish;
		bool stop;
		
	public:
		Timer();
		~Timer() = default;

		void Stop();

		std::chrono::milliseconds GetDurationInMilliseconds();
		std::chrono::seconds GetDurationInSeconds();
	};
}

#endif
