#include "util/errlog.h"
#include <asio.hpp>
#include <fmt/core.h>

int main()
{
    util::setLogLevel(util::LogLevel::Debug);
    util::debug("This is a debug message.");
    util::info(fmt::format("Asio version header-only, io_context ready."));

    asio::io_context io;
    util::info("io_context created successfully.");
    return 0;
}