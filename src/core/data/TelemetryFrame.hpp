#pragma once

#include <cstdint>

namespace fc {

struct TelemetryFrame {
    std::uint64_t timestampMs; 
    double altitude {0.0};
    double accelerationZ {9.81};

    bool altitudeValid {false};
    bool imuValid {false};
};

} //namespace fc