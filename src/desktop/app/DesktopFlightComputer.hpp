#pragma once

#include "core/flight/FlightStateMachine.hpp"
#include "core/services/DataAggregator.hpp"
#include "desktop/logging/FileLogger.hpp"
#include "desktop/sensors/MockBarometerSensor.hpp"
#include "desktop/sensors/MockBatterySensor.hpp"
#include "desktop/sensors/MockIMUSensor.hpp"
#include "desktop/sensors/MockTemperatureSensor.hpp"
#include "desktop/simulation/ScenarioGenerator.hpp"

namespace fc {
class DesktopFlightComputer {
private:
    ScenarioGenerator generator_{};
    MockIMUSensor imu_{};
    MockBarometerSensor barometer_{};
    MockTemperatureSensor temperature_{};
    MockBatterySensor battery_{};
    DataAggregator aggregator_{};
    FlightStateMachine machine_{};
    FileLogger logger_{};
public:
    DesktopFlightComputer() = default;

    bool init();
    void run();

};
}