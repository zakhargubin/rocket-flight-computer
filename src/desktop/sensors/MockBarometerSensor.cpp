#include "desktop/sensors/MockBarometerSensor.hpp"

namespace fc {

    SensorData MockBarometerSensor::read(const ScenarioFrame& frame) const {
        SensorData data{};
        data.kind = SensorKind::Barometer;
        data.timestampMs = frame.timestampMs;
        data.value1 = frame.altitude;
        data.valid = frame.altitudeValid;
        return data;
    }

}