#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace fc {

enum class SensorKind {
    IMU,
    Barometer,
    Temperature,
    Battery
};

enum class ReadStatus {
    Ok,
    Warning,
    Error
};

struct SensorData {
    SensorKind kind {SensorKind::Temperature};
    std::string sensor_name;
    std::uint64_t timestamp_ms {0};
    std::array<double, 6> values {};
    std::size_t value_count {0};
    ReadStatus status {ReadStatus::Ok};
    std::string note;
};

} // namespace fc
