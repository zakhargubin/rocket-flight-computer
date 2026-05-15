#pragma once

#include <cstdint>

namespace fc {

    struct TelemetryFrame {
        std::uint32_t timestampMs{ 0 };

        double altitude{ 0.0 };
        double accelerationZ{ 9.81 };
        double temperature{ 0.0 };
        double batteryVoltage{ 0.0 };

        bool altitudeValid{ false };
        bool imuValid{ false };
        bool temperatureValid{ false };
        bool batteryValid{ false };
    };

}