#include "sensors/IMUSensor.hpp"

namespace fc {

IMUSensor::IMUSensor(const ScenarioGenerator& scenario)
    : Sensor("IMU"), scenario_(scenario) {
}

bool IMUSensor::init() {
    setInitialized(true);
    setHealthy(true);
    return true;
}

SensorData IMUSensor::read(std::uint64_t timestamp_ms) {
    const ScenarioFrame frame = scenario_.frameAt(timestamp_ms);

    SensorData data {};
    data.kind = SensorKind::IMU;
    data.sensor_name = name();
    data.timestamp_ms = timestamp_ms;
    data.values[0] = frame.accel_z_mps2;
    data.values[1] = frame.gyro_z_dps;
    data.value_count = 2;
    data.status = isInitialized() ? ReadStatus::Ok : ReadStatus::Error;
    data.note = isInitialized() ? "imu frame" : "sensor not initialized";
    return data;
}

SensorKind IMUSensor::kind() const {
    return SensorKind::IMU;
}

} // namespace fc
