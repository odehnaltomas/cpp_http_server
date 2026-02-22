cmake_minimum_required(VERSION 3.20)

project(cpp_http_server VERSION 0.1.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

include(ProjectOptions)

# DEPENDENCIES
include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

# fmt
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 12.1.0
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(fmt)

# nlohmann/json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

# Asio (standalone)
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-36-0
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(asio)

# doctest
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(doctest)

# SQLite3
find_package(SQLite3 QUIET)

# TARGETS
add_library(project_options INTERFACE)
setup_project_options(project_options)

add_library(project_warnings INTERFACE)
setup_project_warnings(project_warnings)

add_library(core
    src/util/errlog.cpp
)

target_include_directories(core PUBLIC include)
target_link_libraries(core PUBLIC project_options project_warnings fmt::fmt)

# Asio as header-only: define ASIO_STANDALONE and include dirs
target_compile_definitions(core PUBLIC ASIO_STANDALONE)
target_include_directories(core PUBLIC "${asio_SOURCE_DIR}/asio/include")

add_executable(server
    app/main.cpp
)
target_link_libraries(server PRIVATE core)

if (SQLite3_FOUND)
    target_link_libraries(core PUBLIC SQLite::SQLite3)
    target_compile_definitions(core PUBLIC HAS_SQLITE3=1)
else()
    target_compile_definitions(core PUBLIC HAS_SQLITE3=0)
endif()

enable_testing()
add_executable(test_smoke tests/test_smoke.cpp)
target_link_libraries(test_smoke PRIVATE core doctest::doctest)
add_test(NAME smoke COMMAND test_smoke)