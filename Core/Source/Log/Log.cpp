#include "Log.h"

namespace
{
    std::ofstream logFile;
    std::mutex logMutex;

    std::filesystem::path path;

    Core::LogLevel minLevel = Core::LogLevel::TRACE;

    std::string LevelName(Core::LogLevel level)
    {
        switch (level)
        {
        case Core::LogLevel::TRACE: return "TRACE";
        case Core::LogLevel::DEBUG: return "DEBUG";
        case Core::LogLevel::INFO: return "INFO";
        case Core::LogLevel::WARN: return "WARN";
        case Core::LogLevel::ERR: return "ERROR";
        case Core::LogLevel::CRIT: return "CRIT";
        default: return "UNKNOWN";
        }
    }

    bool Enabled(Core::LogLevel level)
    {
        return static_cast<int>(level) >= static_cast<int>(minLevel);
    }

    std::string GenerateLogFilename()
    {
        const auto now = std::chrono::system_clock::now();
        const auto time = std::chrono::system_clock::to_time_t(now);

        std::tm localTime{};

#ifdef _WIN32
        localtime_s(&localTime, &time);
#else
        localtime_r(&time, &localTime);
#endif

        std::ostringstream filename;

        filename << std::put_time(&localTime, "%Y%m%d_%H%M%S") << ".log";
        return filename.str();
    }

    std::string Timestamp()
    {
        const auto now = std::chrono::system_clock::now();
        const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        const auto time = std::chrono::system_clock::to_time_t(now);

        std::tm localTime{};

#ifdef _WIN32
        localtime_s(&localTime, &time);
#else
        localtime_r(&time, &localTime);
#endif

        std::ostringstream out;
        out << std::put_time(&localTime, "%H:%M:%S") << "." << std::setfill('0') << std::setw(3) << milliseconds.count();

        return out.str();
    }

    std::string LevelColor(Core::LogLevel level)
    {
        switch (level)
        {
        case Core::LogLevel::TRACE: return "\033[90m";
        case Core::LogLevel::DEBUG: return "\033[32m";
        case Core::LogLevel::INFO: return "\033[0m";
        case Core::LogLevel::WARN: return "\033[33m";
        case Core::LogLevel::ERR: return "\033[31m";
        case Core::LogLevel::CRIT: return "\033[2;31m";
        default: return "\033[0m";
        }
    }
}

bool Core::Log::Initialize()
{
    std::scoped_lock lock(logMutex);
    
    try
    {
        const std::filesystem::path directory("Logs");
        std::filesystem::create_directories(directory);

        path = directory / GenerateLogFilename();

        logFile.open(path, std::ios::out | std::ios::app);
        return logFile.is_open();
    }
    catch (const std::filesystem::filesystem_error&)
    {
        return false;
    }
}

void Core::Log::SetLevel(LogLevel level)
{
    std::scoped_lock lock(logMutex);
    minLevel = level;
}

void Core::Log::Write(LogLevel level, std::string_view category, std::string_view message)
{
    std::scoped_lock lock(logMutex);

    if (!Enabled(level))
    {
        return;
    }

    const std::string line = std::format("[{}] [{}] [{}] {}", Timestamp(), LevelName(level), std::string(category), std::string(message));
    const std::string defaultColor = "\033[0m";

    std::print("{}{}{}\n", LevelColor(level), line, defaultColor);

    if (logFile.is_open())
    {
        logFile << "#" << GenerateLogFilename()
            << "\n\n"
            << line 
            << "\n";
        logFile.flush();
    }
}

void Core::Log::Shutdown()
{
    Info("Log", std::format("Log file saved to: '{}'", std::filesystem::absolute(path).generic_string()));
    std::scoped_lock lock(logMutex);

    if (logFile.is_open())
    {
        logFile.flush();
        logFile.close();
    }
}

void Core::Log::Trace(std::string_view category, std::string_view message)
{
    Write(LogLevel::TRACE, category, message);
}

void Core::Log::Debug(std::string_view category, std::string_view message)
{
    Write(LogLevel::DEBUG, category, message);
}

void Core::Log::Info(std::string_view category, std::string_view message)
{
    Write(LogLevel::INFO, category, message);
}

void Core::Log::Warn(std::string_view category, std::string_view message)
{
    Write(LogLevel::WARN, category, message);
}

void Core::Log::Error(std::string_view category, std::string_view message)
{
    Write(LogLevel::ERR, category, message);
}

void Core::Log::Critical(std::string_view category, std::string_view message)
{
    Write(LogLevel::CRIT, category, message);
}

void Core::Log::Test(std::string_view category, std::string_view message)
{
    Trace(category, message);
    Debug(category, message);
    Info(category, message);
    Warn(category, message);
    Error(category, message);
    Critical(category, message);
}
