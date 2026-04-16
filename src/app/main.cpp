#include "core/FlightComputer.hpp"
#include "core/FlightStateMachine.hpp"
#include "core/Logger.hpp"
#include "sensors/BatterySensor.hpp"
#include "sensors/BarometerSensor.hpp"
#include "sensors/IMUSensor.hpp"
#include "sensors/TemperatureSensor.hpp"
#include "simulation/ScenarioGenerator.hpp"

#include <filesystem>
#include <iostream>
#include <memory>

int main() {
    const std::filesystem::path log_file = "flight_log.txt";

    fc::Logger logger;
    if (!logger.open(log_file.string())) {
        std::cerr << "Cannot open log file: " << log_file << '\n';
        return 1;
    }

    fc::ScenarioGenerator scenario;
    fc::FlightStateMachine state_machine;
    fc::FlightComputer computer(logger, state_machine);

    computer.addSensor(std::make_unique<fc::IMUSensor>(scenario));
    computer.addSensor(std::make_unique<fc::BarometerSensor>(scenario));
    computer.addSensor(std::make_unique<fc::TemperatureSensor>(scenario));
    computer.addSensor(std::make_unique<fc::BatterySensor>(scenario));

    const bool init_ok = computer.initSensors();
    if (!init_ok) {
        std::cerr << "Some sensors failed to initialize" << '\n';
    }

    computer.run(500, 45);

    std::cout << "Log saved to: " << log_file << '\n';
    return 0;
}
