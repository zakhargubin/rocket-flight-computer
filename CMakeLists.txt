cmake_minimum_required(VERSION 3.23)
project(RocketFlightComputer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(FC_STRICT_WARNINGS "Enable strict warnings" ON)

add_library(fc_core
    src/core/flight/FlightStateMachine.cpp
)

target_include_directories(fc_core PUBLIC src)

if(FC_STRICT_WARNINGS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(fc_core PRIVATE -Wall -Wextra -Wpedantic)
    elseif(MSVC)
        target_compile_options(fc_core PRIVATE /W4)
    endif()
endif()

add_executable(fc_app
    src/desktop/app/main.cpp
    src/desktop/simulation/ScenarioGenerator.cpp
    src/desktop/logging/FileLogger.cpp
)

target_link_libraries(fc_app PRIVATE fc_core)