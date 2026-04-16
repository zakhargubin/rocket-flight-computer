#include "simulation/ScenarioGenerator.hpp"

#include <algorithm>

namespace fc {

ScenarioFrame ScenarioGenerator::frameAt(std::uint64_t timestamp_ms) const {
    const double t = static_cast<double>(timestamp_ms) / 1000.0;

    ScenarioFrame frame {};
    frame.temperature_c = 22.0 + 0.05 * t;
    frame.battery_v = std::max(11.2, 12.6 - 0.03 * t);

    if (t < 2.0) {
        frame.altitude_m = 0.0;
        frame.accel_z_mps2 = 9.81;
        frame.gyro_z_dps = 0.0;
        return frame;
    }

    if (t < 5.0) {
        const double dt = t - 2.0;
        frame.altitude_m = 60.0 * dt * dt;
        frame.accel_z_mps2 = 24.0;
        frame.gyro_z_dps = 2.0;
        return frame;
    }

    if (t < 10.0) {
        const double dt = t - 5.0;
        frame.altitude_m = 540.0 + 160.0 * dt - 20.0 * dt * dt;
        frame.accel_z_mps2 = 8.5;
        frame.gyro_z_dps = 0.8;
        return frame;
    }

    if (t < 18.0) {
        const double dt = t - 10.0;
        frame.altitude_m = std::max(0.0, 840.0 - 105.0 * dt);
        frame.accel_z_mps2 = 9.4;
        frame.gyro_z_dps = 0.3;
        return frame;
    }

    frame.altitude_m = 0.0;
    frame.accel_z_mps2 = 9.81;
    frame.gyro_z_dps = 0.0;
    return frame;
}

} // namespace fc
