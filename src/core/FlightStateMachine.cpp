#include "core/FlightStateMachine.hpp"

namespace fc {

bool FlightStateMachine::update(const FlightSnapshot& snapshot) {
    FlightState next_state = state_;

    const double delta_altitude = has_previous_altitude_
        ? snapshot.altitude_m - previous_altitude_m_
        : 0.0;

    switch (state_) {
    case FlightState::Idle:
        next_state = FlightState::Ready;
        [[fallthrough]];
    case FlightState::Ready:
        if (snapshot.has_acceleration && snapshot.acceleration_z_mps2 > 15.0) {
            next_state = FlightState::Launch;
        }
        break;

    case FlightState::Launch:
        if (snapshot.has_altitude && delta_altitude > 1.0 && snapshot.altitude_m > 5.0) {
            next_state = FlightState::Ascent;
        }
        break;

    case FlightState::Ascent:
        if (snapshot.has_altitude && delta_altitude <= 0.0 && snapshot.altitude_m > 50.0) {
            next_state = FlightState::Apogee;
        }
        break;

    case FlightState::Apogee:
        if (snapshot.has_altitude && delta_altitude < 0.0) {
            next_state = FlightState::Descent;
        }
        break;

    case FlightState::Descent:
        if (snapshot.has_altitude && snapshot.altitude_m < 1.0) {
            next_state = FlightState::Landed;
        }
        break;

    case FlightState::Landed:
        break;
    }

    if (snapshot.has_altitude) {
        previous_altitude_m_ = snapshot.altitude_m;
        has_previous_altitude_ = true;
    }

    const bool changed = next_state != state_;
    state_ = next_state;
    return changed;
}

FlightState FlightStateMachine::state() const {
    return state_;
}

std::string FlightStateMachine::stateName() const {
    switch (state_) {
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

} // namespace fc
