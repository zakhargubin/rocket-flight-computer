#pragma once

#include <cstdint>

namespace fc {

    enum class SensorKind {
        IMU,
        Barometer,
        Temperature,
        Battery
    };

    struct SensorData {
        SensorKind kind;
        std::uint32_t timestampMs{ 0 };

        double value1{ 0.0 };
        double value2{ 0.0 };
        double value3{ 0.0 };

        bool valid{ false };
    };

}