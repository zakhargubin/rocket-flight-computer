#include "desktop/sensors/MockIMUSensor.hpp"

namespace fc {

    SensorData MockIMUSensor::read(const ScenarioFrame& frame) const {
        SensorData data{};
        data.kind = SensorKind::IMU;
        data.timestampMs = frame.timestampMs;
        data.value1 = frame.accelerationZ;
        data.valid = frame.imuValid;
        return data;
    }

}