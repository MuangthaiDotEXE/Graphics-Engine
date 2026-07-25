#pragma once

#ifndef TIMER_H
#define TIMER_H

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
		std::chrono::milliseconds GetDurationInSeconds();
	};
}

#endif
