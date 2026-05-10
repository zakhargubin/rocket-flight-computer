#include "core/flight/FlightStateMachine.hpp"

namespace fc {

const char* toString(FlightState state) {
    switch (state)
    {
    case FlightState::Idle:
        return "Idle";
    case FlightState::Ready:
        return "Ready";
    case FlightState::Launch:
        return "Launch";
    case FlightState::Ascent:
        return "Ascent";
    case FlightState::Apogee:
        return "Apogee";
    case FlightState::Descent:
        return "Descent";
    case FlightState::Landed:
        return "Landed";
    }

    return "Unknown";
}

FlightState FlightStateMachine::update(const TelemetryFrame& frame) {
    
    const double deltaAltitude = hasPreviousAltitude_ ? (frame.altitude - previousAltitude_) : 0.0;

    switch (currentState_)
    {
    case FlightState::Idle:
        currentState_ = FlightState::Ready;
        break;
    case FlightState::Ready:
        if (frame.imuValid && frame.accelerationZ > 15.0) {
            currentState_ = FlightState::Launch;
        }
        break;
    case FlightState::Launch:
        if (frame.altitudeValid && frame.altitude > 5.5 && deltaAltitude > 1.0) { //frame.altitude > 5.5, 5.5?
            currentState_ = FlightState::Ascent;
        }
        break;
    case FlightState::Ascent:
        if (frame.altitudeValid && frame.altitude > 50 && deltaAltitude <= 0) { //frame.altitude > 50.0, 50.0?
            currentState_ = FlightState::Apogee;
        }
        break;
    case FlightState::Apogee:
        if (frame.altitudeValid && deltaAltitude < 0) {
            currentState_ = FlightState::Descent;
        }
        break;
    case FlightState::Descent:
        if (frame.altitudeValid && frame.altitude < 1.0) {
            currentState_ = FlightState::Landed;
        }
        break;
    case FlightState::Landed:
        break;
    }

    if (frame.altitudeValid) {
        previousAltitude_ = frame.altitude;
        hasPreviousAltitude_ = true;
    }

    return currentState_;
}

FlightState  FlightStateMachine::state() const {
    return currentState_;
}

void FlightStateMachine::reset() {
    currentState_ = FlightState::Idle;
    previousAltitude_ = 0.0;
    hasPreviousAltitude_ = false;
}


} // namespace fc