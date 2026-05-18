#include "core/monitoring/SystemEvent.hpp"

namespace fc {

const char* toString(EventSeverity severity) {
    switch (severity) {
    case EventSeverity::Warning:
        return "Warning";
    case EventSeverity::Error:
        return "Error";
    }

    return "Unknown";
}

const char* toString(EventCode code) {
    switch (code) {
    case EventCode::AltitudeSensorInvalid:
        return "AltitudeSensorInvalid";
    case EventCode::ImuSensorInvalid:
        return "ImuSensorInvalid";
    case EventCode::TemperatureSensorInvalid:
        return "TemperatureSensorInvalid";
    case EventCode::BatterySensorInvalid:
        return "BatterySensorInvalid";
    case EventCode::BatteryLow:
        return "BatteryLow";
    case EventCode::BatteryCritical:
        return "BatteryCritical";
    case EventCode::TemperatureHigh:
        return "TemperatureHigh";
    case EventCode::AltitudeNegative:
        return "AltitudeNegative";
    }

    return "Unknown";
}

}