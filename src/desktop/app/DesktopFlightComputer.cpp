#include "desktop/app/DesktopFlightComputer.hpp"

#include <iostream>

namespace fc {

    bool DesktopFlightComputer::init() {
        if (!logger_.open("flight_log.txt")) {
            return false;
        }

        logger_.logMessage("Flight log started");
        return true;
    }

    void DesktopFlightComputer::run() {
        while (generator_.hasNext()) {
            const ScenarioFrame scenarioFrame = generator_.next();

            const SensorData imuData = imu_.read(scenarioFrame);
            const SensorData baroData = barometer_.read(scenarioFrame);
            const SensorData temperatureData = temperature_.read(scenarioFrame);
            const SensorData batteryData = battery_.read(scenarioFrame);

            aggregator_.reset();
            aggregator_.add(imuData);
            aggregator_.add(baroData);
            aggregator_.add(temperatureData);
            aggregator_.add(batteryData);

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