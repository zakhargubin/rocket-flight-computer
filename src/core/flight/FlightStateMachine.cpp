#include "core/flight/FlightStateMachine.hpp"

namespace fc {

    namespace {
        constexpr double kLaunchAccelerationThreshold = 1.30; // g
        constexpr double kAscentAltitudeThreshold = 3.0;      // m
        constexpr double kAscentDeltaThreshold = 0.30;        // m per frame
        constexpr double kApogeeMinAltitude = 20.0;           // m
        constexpr double kDescentDeltaThreshold = -0.20;      // m per frame
        constexpr double kLandedAltitudeThreshold = 2.0;      // m
    } // namespace

    const char* toString(FlightState state) {
        switch (state) {
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
        const double deltaAltitude =
            hasPreviousAltitude_ ? (frame.altitude - previousAltitude_) : 0.0;

        switch (currentState_) {
        case FlightState::Idle:
            currentState_ = FlightState::Ready;
            break;

        case FlightState::Ready:
            if (frame.imuValid &&
                frame.accelerationZ > kLaunchAccelerationThreshold) {
                currentState_ = FlightState::Launch;
            }
            break;

        case FlightState::Launch:
            if (frame.altitudeValid &&
                frame.altitude > kAscentAltitudeThreshold &&
                deltaAltitude > kAscentDeltaThreshold) {
                currentState_ = FlightState::Ascent;
            }
            break;

        case FlightState::Ascent:
            if (frame.altitudeValid &&
                frame.altitude > kApogeeMinAltitude &&
                deltaAltitude <= 0.0) {
                currentState_ = FlightState::Apogee;
            }
            break;

        case FlightState::Apogee:
            if (frame.altitudeValid &&
                deltaAltitude < kDescentDeltaThreshold) {
                currentState_ = FlightState::Descent;
            }
            break;

        case FlightState::Descent:
            if (frame.altitudeValid &&
                frame.altitude < kLandedAltitudeThreshold) {
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

    FlightState FlightStateMachine::state() const {
        return currentState_;
    }

    void FlightStateMachine::reset() {
        currentState_ = FlightState::Idle;
        previousAltitude_ = 0.0;
        hasPreviousAltitude_ = false;
    }

}