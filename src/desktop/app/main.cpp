#include "core/flight/FlightStateMachine.hpp"
#include "desktop/simulation/ScenarioGenerator.hpp"

#include <iostream>
#include <vector>

int main() {
    fc::ScenarioGenerator generator;
    fc::FlightStateMachine machine;

    while (generator.hasNext()) {
        const fc::TelemetryFrame frame = generator.next();
        const fc::FlightState state = machine.update(frame);

        std::cout
            << "t = " << frame.timestampMs << " ms"
            << ", altitude = " << frame.altitude
            << ", az = " << frame.accelerationZ
            << ", state = " << fc::toString(state)
            << '\n';
    }

    return 0;
}