#include "CoreLog.h"

std::shared_ptr<spdlog::logger> CoreLog::s_Logger;

void CoreLog::Init() {
    // Create console sink (colored output) and file sink
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace); // Adjust the level if needed

    // Create logger instance
    s_Logger = std::make_shared<spdlog::logger>("REALITY_LOG", console_sink);

    // Set the default logger to be used globally
    spdlog::set_default_logger(s_Logger);
}

void CoreLog::Log(LogLevel level, const char* message) {
    switch (level) {
    case LogLevel::Trace:
        s_Logger->trace(message);
        break;
    case LogLevel::Debug:
        s_Logger->debug(message);
        break;
    case LogLevel::Info:
        s_Logger->info(message);
        break;
    case LogLevel::Warning:
        s_Logger->warn(message);
        break;
    case LogLevel::Error:
        s_Logger->error(message);
        break;
    case LogLevel::Critical:
        s_Logger->critical(message);
        break;
    }
}