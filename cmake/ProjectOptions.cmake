include_guard()

function(setup_project_options target)
    target_compile_features(${target} INTERFACE cxx_std_20)
    if(MSVC)
        target_compile_options(${target} INTERFACE /permissive-)
    endif()

    set(CMAKE_EXPORT_COMPILE_COMMANDS ON PARENT_SCOPE)
endfunction()

function(setup_project_warnings target)
    if (MSVC)
        target_compile_options(${target} INTERFACE /W4 /permissive-)
    else()
        target_compile_options(${target} INTERFACE -Wall -Wextra -Wpedantic)
    endif()
endfunction()