#include "core/flight/FlightStateMachine.hpp"
#include "desktop/logging/FileLogger.hpp"
#include "desktop/simulation/ScenarioGenerator.hpp"

#include <iostream>
#include <vector>

int main() {
    fc::ScenarioGenerator generator;
    fc::FlightStateMachine machine;
    fc::FileLogger logger;

    if (!logger.open("flight_log.txt")) {
        std::cerr << "Failed to open log file\n";
        return 1;
    }

    logger.logMessage("Flight log started");

    while (generator.hasNext()) {
        const fc::TelemetryFrame frame = generator.next();
        const fc::FlightState state = machine.update(frame);

        std::cout
            << "t = " << frame.timestampMs << " ms"
            << ", altitude = " << frame.altitude
            << ", az = " << frame.accelerationZ
            << ", state = " << fc::toString(state)
            << '\n';
        logger.logFrame(frame, state);
    }

    logger.logMessage("Flight log finished");
    logger.close();

    return 0;
}