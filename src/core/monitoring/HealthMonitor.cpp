#include "core/monitoring/HealthMonitor.hpp"

namespace fc {

std::vector<SystemEvent> HealthMonitor::check(const TelemetryFrame& frame) const {
    std::vector<SystemEvent> events;

    if (!frame.altitudeValid) {
        events.push_back({ EventSeverity::Warning, EventCode::AltitudeSensorInvalid, frame.timestampMs });
    }

    if (!frame.imuValid) {
        events.push_back({ EventSeverity::Warning, EventCode::ImuSensorInvalid, frame.timestampMs });
    }

    if (!frame.temperatureValid) {
        events.push_back({ EventSeverity::Warning, EventCode::TemperatureSensorInvalid, frame.timestampMs });
    }

    if (!frame.batteryValid) {
        events.push_back({ EventSeverity::Warning, EventCode::BatterySensorInvalid, frame.timestampMs });
    }

    if (frame.altitudeValid && frame.altitude < 0.0) {
        events.push_back({ EventSeverity::Error, EventCode::AltitudeNegative, frame.timestampMs });
    }

    if (frame.temperatureValid && frame.temperature > 60.0) {
        events.push_back({ EventSeverity::Warning, EventCode::TemperatureHigh, frame.timestampMs });
    }

    if (frame.batteryValid && frame.batteryVoltage < 10.5) {
        events.push_back({ EventSeverity::Error, EventCode::BatteryCritical, frame.timestampMs });
    }
    else if (frame.batteryValid && frame.batteryVoltage < 11.0) {
        events.push_back({ EventSeverity::Warning, EventCode::BatteryLow, frame.timestampMs });
    }

    return events;
}

}