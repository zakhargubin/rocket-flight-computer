#include "desktop/sensors/MockTemperatureSensor.hpp"

namespace fc {

    SensorData MockTemperatureSensor::read(const ScenarioFrame& frame) const {
        SensorData data{};
        data.kind = SensorKind::Temperature;
        data.timestampMs = frame.timestampMs;
        data.value1 = frame.temperature;
        data.valid = frame.temperatureValid;
        return data;
    }

}