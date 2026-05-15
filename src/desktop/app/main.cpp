#include "core/flight/FlightStateMachine.hpp"
#include "core/services/DataAggregator.hpp"
#include "desktop/logging/FileLogger.hpp"
#include "desktop/sensors/MockBarometerSensor.hpp"
#include "desktop/sensors/MockBatterySensor.hpp"
#include "desktop/sensors/MockIMUSensor.hpp"
#include "desktop/sensors/MockTemperatureSensor.hpp"
#include "desktop/simulation/ScenarioGenerator.hpp"

#include <iostream>

int main() {
    fc::ScenarioGenerator generator;
    fc::MockIMUSensor imu;
    fc::MockBarometerSensor barometer;
    fc::MockTemperatureSensor temperature;
    fc::MockBatterySensor battery;
    fc::DataAggregator aggregator;
    fc::FlightStateMachine machine;
    fc::FileLogger logger;

    if (!logger.open("flight_log.txt")) {
        std::cerr << "Failed to open log file\n";
        return 1;
    }

    logger.logMessage("Flight log started");

    while (generator.hasNext()) {
        const fc::ScenarioFrame scenarioFrame = generator.next();

        const fc::SensorData imuData = imu.read(scenarioFrame);
        const fc::SensorData baroData = barometer.read(scenarioFrame);
        const fc::SensorData temperatureData = temperature.read(scenarioFrame);
        const fc::SensorData batteryData = battery.read(scenarioFrame);

        aggregator.reset();
        aggregator.add(imuData);
        aggregator.add(baroData);
        aggregator.add(temperatureData);
        aggregator.add(batteryData);

        const fc::TelemetryFrame frame = aggregator.buildFrame();
        const fc::FlightState state = machine.update(frame);

        std::cout
            << "t = " << frame.timestampMs << " ms"
            << ", altitude = " << frame.altitude
            << ", az = " << frame.accelerationZ
            << ", temperature = " << frame.temperature
            << ", battery = " << frame.batteryVoltage
            << ", state = " << fc::toString(state)
            << '\n';

        logger.logFrame(frame, state);
    }

    logger.logMessage("Flight log finished");
    logger.close();

    return 0;
}