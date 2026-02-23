#include "util/errlog.h"
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <atomic>
#include <mutex>
#include <chrono>

namespace util
{
    static std::atomic<LogLevel> currentLogLevel{LogLevel::Info};
    static std::mutex printMutex;

    void setLogLevel(LogLevel level)
    {
        currentLogLevel.store(level, std::memory_order_relaxed);
    }

    static constexpr std::string_view to_str(LogLevel lvl) {
        switch (lvl) {
            case LogLevel::Debug:   return "DEBUG";
            case LogLevel::Info:    return "INFO";
            case LogLevel::Notice:  return "NOTICE";
            case LogLevel::Warn:    return "WARN";
            case LogLevel::Error:   return "ERROR";
        }
        return "INFO";
    }

    static inline bool shouldLog(LogLevel msgLevel, LogLevel currentLevel)
    {
        return static_cast<int>(msgLevel) >= static_cast<int>(currentLevel);
    }

    void log(LogLevel level, std::string_view message)
    {
        const auto currentLevel = currentLogLevel.load(std::memory_order_relaxed);
        if (!shouldLog(level, currentLevel)) {
            return;
        }

        // Timestamp with milisecond precision
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::tm tm{};
        #ifdef _WIN32
            localtime_s(&tm, &time);
        #else
            localtime_r(&time, &tm);
        #endif

        std::scoped_lock lock(printMutex);
        fmt::print("[{:%Y-%m-%d %H:%M:%S}.{:03}] [{}] {}\n", tm, ms.count(), to_str(level), message);
        // fmt::print("Version: {}\n", FMT_VERSION);
    }

    void debug (std::string_view msg) { log(LogLevel::Debug,  msg); }
    void info  (std::string_view msg) { log(LogLevel::Info,   msg); }
    void notice(std::string_view msg) { log(LogLevel::Notice, msg); }
    void warn  (std::string_view msg) { log(LogLevel::Warn,   msg); }
    void error (std::string_view msg) { log(LogLevel::Error,  msg); }
}