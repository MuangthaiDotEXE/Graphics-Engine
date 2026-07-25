#include "Timer.h"

Engine::Timer::Timer()
	: start(std::chrono::high_resolution_clock::now()), stop(false)
{
}

void Engine::Timer::Stop()
{
	finish = std::chrono::high_resolution_clock::now();
	stop = true;
}

std::chrono::milliseconds Engine::Timer::GetDurationInMilliseconds()
{
	if (!stop)
	{
		Stop();
	}

	return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
}

std::chrono::milliseconds Engine::Timer::GetDurationInSeconds()
{
	if (!stop)
	{
		Stop();
	}
	
	return std::chrono::duration_cast<std::chrono::seconds>(finish - start);
}
