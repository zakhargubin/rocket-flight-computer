#include "sensors/BatterySensor.hpp"

namespace fc {

BatterySensor::BatterySensor(const ScenarioGenerator& scenario)
    : Sensor("Battery"), scenario_(scenario) {
}

bool BatterySensor::init() {
    setInitialized(true);
    setHealthy(true);
    return true;
}

SensorData BatterySensor::read(std::uint64_t timestamp_ms) {
    const ScenarioFrame frame = scenario_.frameAt(timestamp_ms);

    SensorData data {};
    data.kind = SensorKind::Battery;
    data.sensor_name = name();
    data.timestamp_ms = timestamp_ms;
    data.values[0] = frame.battery_v;
    data.value_count = 1;
    data.status = frame.battery_v < 11.5 ? ReadStatus::Warning : ReadStatus::Ok;
    data.note = frame.battery_v < 11.5 ? "battery is low" : "battery is normal";
    return data;
}

SensorKind BatterySensor::kind() const {
    return SensorKind::Battery;
}

} // namespace fc
