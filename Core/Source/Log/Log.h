#pragma once

#ifndef CORE_LOG_H
#define CORE_LOG_H

#include <chrono>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <print>
#include <format>
#include <mutex>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>

namespace Core
{
	enum struct LogLevel
	{
		TRACE,
		DEBUG,
		INFO,
		WARN,
		ERR,
		CRITICAL
	};

	class Log
	{
	public:
		Log() = default;
		virtual ~Log() = default;

		static bool Initialize();
		static void SetLevel(LogLevel level);
		static void Write(LogLevel level, std::string_view category, std::string_view message);
		static void Shutdown();

		static void Trace(std::string_view category, std::string_view message);
		static void Debug(std::string_view category, std::string_view message);
		static void Info(std::string_view category, std::string_view message);
		static void Warn(std::string_view category, std::string_view message);
		static void Error(std::string_view category, std::string_view message);
		static void Critical(std::string_view category, std::string_view message);

		static void Test(std::string_view category, std::string_view message);
	};
}

#endif
