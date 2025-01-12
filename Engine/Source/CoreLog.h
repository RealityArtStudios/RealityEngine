#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Critical
};

// CoreLog class to wrap spdlog functionality
class CoreLog {
public:
    // Initialize the logger
    static void Init();

    // Log functions for different log levels
    static void Log(LogLevel level, const char* message);

private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};

// Define the REALITY_LOG macro
#define REALITY_LOG(level, message) CoreLog::Log(LogLevel::level, message)