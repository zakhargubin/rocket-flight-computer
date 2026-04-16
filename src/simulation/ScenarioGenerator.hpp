#pragma once

#include <cstdint>

namespace fc {

struct ScenarioFrame {
    double altitude_m {0.0};
    double accel_z_mps2 {9.81};
    double gyro_z_dps {0.0};
    double temperature_c {22.0};
    double battery_v {12.6};
};

class ScenarioGenerator {
public:
    ScenarioFrame frameAt(std::uint64_t timestamp_ms) const;
};

}
