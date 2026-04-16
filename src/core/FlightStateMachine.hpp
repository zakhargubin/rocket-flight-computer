#pragma once

#include <string>

namespace fc {

enum class FlightState {
    Idle,
    Ready,
    Launch,
    Ascent,
    Apogee,
    Descent,
    Landed
};

struct FlightSnapshot {
    bool has_altitude {false};
    bool has_acceleration {false};
    double altitude_m {0.0};
    double acceleration_z_mps2 {9.81};
};

class FlightStateMachine {
public:
    FlightStateMachine() = default;

    bool update(const FlightSnapshot& snapshot);
    FlightState state() const;
    std::string stateName() const;

private:
    FlightState state_ {FlightState::Idle};
    bool has_previous_altitude_ {false};
    double previous_altitude_m_ {0.0};
};

} // namespace fc
