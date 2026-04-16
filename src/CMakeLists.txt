add_library(flight_computer_core)

target_sources(flight_computer_core
    PRIVATE
        core/Sensor.cpp
        core/Logger.cpp
        core/FlightStateMachine.cpp
        core/FlightComputer.cpp
        sensors/IMUSensor.cpp
        sensors/BarometerSensor.cpp
        sensors/TemperatureSensor.cpp
        sensors/BatterySensor.cpp
        simulation/ScenarioGenerator.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
            core/Sensor.hpp
            core/Logger.hpp
            core/FlightStateMachine.hpp
            core/FlightComputer.hpp
            sensors/IMUSensor.hpp
            sensors/BarometerSensor.hpp
            sensors/TemperatureSensor.hpp
            sensors/BatterySensor.hpp
            simulation/ScenarioGenerator.hpp
)

target_compile_features(flight_computer_core PUBLIC cxx_std_17)

add_executable(flight_computer_app app/main.cpp)
target_link_libraries(flight_computer_app PRIVATE flight_computer_core)
