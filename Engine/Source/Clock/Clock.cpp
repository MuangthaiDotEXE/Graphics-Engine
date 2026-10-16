#include "Clock.h"

Engine::Clock::Clock()
	: start(std::chrono::steady_clock::now()), stop(false)
{
}

void Engine::Clock::Stop()
{
	finish = std::chrono::steady_clock::now();
	stop = true;
}

char* Engine::Clock::GetTime()
{
	auto now = std::chrono::system_clock::now();
	std:time_t time = std::chrono::system_clock::to_time_t(now);

	return std::ctime(&time);
}

std::chrono::milliseconds Engine::Clock::GetDurationInMilliseconds()
{
	if (!stop)
	{
		Stop();
	}

	return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
}

std::chrono::seconds Engine::Clock::GetDurationInSeconds()
{
	if (!stop)
	{
		Stop();
	}
	
	return std::chrono::duration_cast<std::chrono::seconds>(finish - start);
}
