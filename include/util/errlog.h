#pragma once

#include <string_view>
#include <fmt/core.h>

namespace util
{
    // Log levels for the logging system
    enum class LogLevel
    {
        Debug,
        Info,
        Notice,
        Warn,
        Error,
    };

    // Set the current log level. Messages below this level will be ignored.
    void setLogLevel(LogLevel level);

    void log(LogLevel level, std::string_view message);

    template<typename... Args>
    inline void logf(LogLevel level, fmt::format_string<Args...> format, Args&&... args)
    {
        log(level, fmt::format(format, std::forward<Args>(args)...));
    }

    void debug(std::string_view message);
    void info(std::string_view message);
    void notice(std::string_view message);
    void warn(std::string_view message);
    void error(std::string_view message);

    template<typename... Args>
    inline void debugf(fmt::format_string<Args...> format, Args&&... args)
    {
        logf(LogLevel::Debug, format, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void infof(fmt::format_string<Args...> format, Args&&... args)
    {
        logf(LogLevel::Info, format, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void noticef(fmt::format_string<Args...> format, Args&&... args)
    {
        logf(LogLevel::Notice, format, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void warnf(fmt::format_string<Args...> format, Args&&... args)
    {
        logf(LogLevel::Warn, format, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void errorf(fmt::format_string<Args...> format, Args&&... args)
    {
        logf(LogLevel::Error, format, std::forward<Args>(args)...);
    }
}   // namespace util