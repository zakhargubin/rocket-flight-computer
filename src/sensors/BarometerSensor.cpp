#include "sensors/BarometerSensor.hpp"

namespace fc {

BarometerSensor::BarometerSensor(const ScenarioGenerator& scenario)
    : Sensor("Barometer"), scenario_(scenario) {
}

bool BarometerSensor::init() {
    setInitialized(true);
    setHealthy(true);
    return true;
}

SensorData BarometerSensor::read(std::uint64_t timestamp_ms) {
    const ScenarioFrame frame = scenario_.frameAt(timestamp_ms);

    SensorData data {};
    data.kind = SensorKind::Barometer;
    data.sensor_name = name();
    data.timestamp_ms = timestamp_ms;
    data.values[0] = frame.altitude_m;
    data.value_count = 1;
    data.status = isInitialized() ? ReadStatus::Ok : ReadStatus::Error;
    data.note = isInitialized() ? "altitude estimate" : "sensor not initialized";
    return data;
}

SensorKind BarometerSensor::kind() const {
    return SensorKind::Barometer;
}

} // namespace fc
