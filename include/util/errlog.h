#pragma once

#include <string_view>

namespace util
{
    enum class LogLevel
    {
        Debug,
        Info,
        Notice,
        Warn,
        Error,
    };

    void setLogLevel(LogLevel level);

    void log(LogLevel level, std::string_view message);

    void debug(std::string_view message);
    void info(std::string_view message);
    void notice(std::string_view message);
    void warn(std::string_view message);
    void error(std::string_view message);
}   // namespace util