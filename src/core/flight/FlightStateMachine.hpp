#pragma once

#include "core/data/TelemetryFrame.hpp"
#include "core/flight/FlightState.hpp"

namespace fc {

class FlightStateMachine {
private:
    FlightState currentState_ {FlightState::Idle};
    double previousAltitude_ {0.0};
    bool hasPreviousAltitude_ {false};
public:
    FlightStateMachine() = default;

    FlightState update(const TelemetryFrame& frame);
    FlightState state() const;
    void reset();
};

} //namespace fc