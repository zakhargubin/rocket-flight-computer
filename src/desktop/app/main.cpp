#include "core/flight/FlightStateMachine.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<fc::TelemetryFrame> frames {
        {0,    0.0,   9.81, true, true},
        {500,  0.0,   9.81, true, true},
        {1000, 0.0,   18.0, true, true},
        {1500, 8.0,   17.0, true, true},
        {2000, 35.0,  14.0, true, true},
        {2500, 90.0,  10.0, true, true},
        {3000, 120.0,  9.0, true, true},
        {3500, 118.0,  9.0, true, true},
        {4000, 95.0,   9.0, true, true},
        {4500, 50.0,   9.0, true, true},
        {5000, 10.0,   9.0, true, true},
        {5500, 0.0,    9.0, true, true}
    };

    fc::FlightStateMachine machine;

    for (const fc::TelemetryFrame& frame : frames) {
        const fc::FlightState state = machine.update(frame);

        std::cout
            << "t = " << frame.timestampMs << "ms"
            << ", altitude = " << frame.altitude
            << ", az = " << frame.accelerationZ
            << ", state = " << fc::toString(state)
            << '\n';

    }

    return 0;
}