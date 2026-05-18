#pragma once

#include <cstdint>

namespace fc {

enum class EventSeverity {
    Warning,
    Error
};

enum class EventCode {
    AltitudeSensorInvalid,
    ImuSensorInvalid,
    TemperatureSensorInvalid,
    BatterySensorInvalid,
    BatteryLow,
    BatteryCritical,
    TemperatureHigh,
    AltitudeNegative
};

struct SystemEvent {
    EventSeverity severity;
    EventCode code;
    std::uint32_t timestampMs{ 0 };
};

const char* toString(EventSeverity severity);
const char* toString(EventCode code);

}