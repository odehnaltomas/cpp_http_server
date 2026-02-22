#include "util/errlog.h"
#include <fmt/core.h>
#include <atomic>

namespace util
{
    static std::atomic<LogLevel> currentLogLevel{LogLevel::Info};

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

    void log(LogLevel level, std::string_view message)
    {
        if (level < currentLogLevel.load(std::memory_order_relaxed)) {
            return;
        }
        fmt::print("[{}] {}\n", to_str(level), message);
    }

    void debug (std::string_view msg) { log(LogLevel::Debug,  msg); }
    void info  (std::string_view msg) { log(LogLevel::Info,   msg); }
    void notice(std::string_view msg) { log(LogLevel::Notice, msg); }
    void warn  (std::string_view msg) { log(LogLevel::Warn,   msg); }
    void error (std::string_view msg) { log(LogLevel::Error,  msg); }
}