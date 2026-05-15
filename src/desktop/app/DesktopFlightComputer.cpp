#include "desktop/app/DesktopFlightComputer.hpp"

#include <iostream>

namespace fc {

    bool DesktopFlightComputer::init() {
        sensors_.push_back(&imu_);
        sensors_.push_back(&barometer_);
        sensors_.push_back(&temperature_);
        sensors_.push_back(&battery_);

        if (!logger_.open("flight_log.txt")) {
            return false;
        }

        logger_.logMessage("Flight log started");
        return true;
    }

    void DesktopFlightComputer::run() {
        while (generator_.hasNext()) {
            const ScenarioFrame scenarioFrame = generator_.next();

            aggregator_.reset();

            for (const Sensor* sensor : sensors_) {
                aggregator_.add(sensor->read(scenarioFrame));
            }

            const TelemetryFrame frame = aggregator_.buildFrame();
            const FlightState state = machine_.update(frame);

            std::cout
                << "t = " << frame.timestampMs << " ms"
                << ", altitude = " << frame.altitude
                << ", az = " << frame.accelerationZ
                << ", temperature = " << frame.temperature
                << ", battery = " << frame.batteryVoltage
                << ", state = " << toString(state)
                << '\n';

            logger_.logFrame(frame, state);
        }

        logger_.logMessage("Flight log finished");
        logger_.close();
    }

}