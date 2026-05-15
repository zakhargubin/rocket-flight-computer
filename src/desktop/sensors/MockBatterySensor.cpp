#include "desktop/sensors/MockBatterySensor.hpp"

namespace fc {

    SensorData MockBatterySensor::read(const ScenarioFrame& frame) const {
        SensorData data{};
        data.kind = SensorKind::Battery;
        data.timestampMs = frame.timestampMs;
        data.value1 = frame.batteryVoltage;
        data.valid = frame.batteryValid;
        return data;
    }

}