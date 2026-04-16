cmake_minimum_required(VERSION 3.23)
project(RocketFlightComputer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(FC_BUILD_TESTS "Build tests" ON)
option(FC_ENABLE_STRICT_WARNINGS "Enable strict warnings" OFF)

add_subdirectory(src)

if(FC_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(FC_ENABLE_STRICT_WARNINGS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(flight_computer_core PRIVATE -Wall -Wextra -Wpedantic)
    elseif(MSVC)
        target_compile_options(flight_computer_core PRIVATE /W4)
    endif()
endif()









