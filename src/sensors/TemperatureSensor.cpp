#include "sensors/TemperatureSensor.hpp"

namespace fc {

TemperatureSensor::TemperatureSensor(const ScenarioGenerator& scenario)
    : Sensor("Temperature"), scenario_(scenario) {
}

bool TemperatureSensor::init() {
    setInitialized(true);
    setHealthy(true);
    return true;
}

SensorData TemperatureSensor::read(std::uint64_t timestamp_ms) {
    const ScenarioFrame frame = scenario_.frameAt(timestamp_ms);

    SensorData data {};
    data.kind = SensorKind::Temperature;
    data.sensor_name = name();
    data.timestamp_ms = timestamp_ms;
    data.values[0] = frame.temperature_c;
    data.value_count = 1;
    data.status = isInitialized() ? ReadStatus::Ok : ReadStatus::Error;
    data.note = isInitialized() ? "internal temperature" : "sensor not initialized";
    return data;
}

SensorKind TemperatureSensor::kind() const {
    return SensorKind::Temperature;
}

} // namespace fc
