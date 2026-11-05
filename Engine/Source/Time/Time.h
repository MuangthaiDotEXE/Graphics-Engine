#pragma once

#ifndef ENGINE_TIME_H
#define ENGINE_TIME_H

#include <chrono>
#include <cstdint>
#include <cmath>
#include <algorithm>

namespace Engine
{
	class Time
	{
	public:
		static inline std::chrono::steady_clock::time_point startTime{};
		static inline std::chrono::steady_clock::time_point lastTime{};
		static inline bool initialize = false;

		static inline double deltaTime = 0.0;
		static inline double unscaledDeltaTime = 0.0;
		static inline double timeSinceStart = 0.0;
		static inline double unscaledTimeSinceStart = 0.0;
		static inline double realtimeSinceStartup = 0.0;

		static inline double rawDelta = 0.0;
		static inline double smoothedDelta = 0.0;

		static inline double timeScale = 1.0;
		static inline double maximumDeltaTime = 0.1;

		static inline double fpsSmoothingTime = 0.5;

		static inline uint64_t frameCount = 0;

	public:
		Time() = delete;

		static void Update();
		static void Reset();

		static float DeltaTime();
		static float UnscaledDeltaTime();

		static double TimeSinceStart();
		static double UnscaledTimeSinceStart();
		static double RealtimeSinceStartup();

		static float FPS();
		static float InstantFPS();
		static float FrameTimeMilliseconds();

		static float GetTimeScale();
		static float GetFPSSmoothingTime();

		static void SetTimeScale(float scale);
		static void SetFPSSmoothingTime(float seconds);

		static uint64_t FrameCount();
	};
}

#endif
