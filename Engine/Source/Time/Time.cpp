#include "Time.h"

void Engine::Time::Update()
{
	const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

	if (!initialize)
	{
		startTime = now;
		lastTime = now;
		initialize = true;

		deltaTime = unscaledDeltaTime = rawDelta = smoothedDelta = 0.0;
		frameCount = 1;

		return;
	}

	rawDelta = std::max(0.0, std::chrono::duration<double>(now - lastTime).count());
	lastTime = now;

	realtimeSinceStartup = std::chrono::duration<double>(now - startTime).count();

	unscaledDeltaTime = std::min(rawDelta, maximumDeltaTime);
	deltaTime = unscaledDeltaTime * timeScale;

	unscaledTimeSinceStart += unscaledDeltaTime;
	timeSinceStart += deltaTime;

	if (smoothedDelta <= 0.0)
	{
		smoothedDelta = rawDelta;
	}
	else if (rawDelta > 0.0)
	{
		const double alpha = 1.0 - std::exp(-rawDelta / std::max(fpsSmoothingTime, 1e-6));
		smoothedDelta += (rawDelta - smoothedDelta) * alpha;
	}

	++frameCount;
}

void Engine::Time::Reset()
{
	initialize = false;
	deltaTime = unscaledDeltaTime = 0.0;
	timeSinceStart = unscaledTimeSinceStart = realtimeSinceStartup = 0.0;
	rawDelta = smoothedDelta = 0.0;
	frameCount = 0;
}

float Engine::Time::DeltaTime()
{
	return static_cast<float>(deltaTime);
}

float Engine::Time::UnscaledDeltaTime()
{
	return static_cast<float>(unscaledDeltaTime);
}

double Engine::Time::TimeSinceStart()
{
	return timeSinceStart;
}

double Engine::Time::UnscaledTimeSinceStart()
{
	return unscaledTimeSinceStart;
}

double Engine::Time::RealtimeSinceStartup()
{
	return realtimeSinceStartup;
}

float Engine::Time::FPS()
{
	return smoothedDelta > 0.0 ? static_cast<float>(1.0 / smoothedDelta) : 0.0f;
}

float Engine::Time::InstantFPS()
{
	return rawDelta > 0.0 ? static_cast<float>(1.0 / rawDelta) : 0.0;
}

float Engine::Time::FrameTimeMilliseconds()
{
	return static_cast<float>(smoothedDelta * 1000.0);
}

float Engine::Time::GetTimeScale()
{
	return static_cast<float>(timeScale);
}

float Engine::Time::GetFPSSmoothingTime()
{
	return static_cast<float>(fpsSmoothingTime);
}

void Engine::Time::SetTimeScale(float scale)
{
	timeScale = std::max(0.0f, scale);
}

void Engine::Time::SetFPSSmoothingTime(float seconds)
{
	fpsSmoothingTime = std::max(0.0f, seconds);
}

uint64_t Engine::Time::FrameCount()
{
	return frameCount;
}
