#include "desktop/simulation/ScenarioGenerator.hpp"

namespace fc {

    bool ScenarioGenerator::hasNext() const {
        return step_ < maxSteps_;
    }

    TelemetryFrame ScenarioGenerator::next() {
        const std::uint32_t currentStep = step_;
        ++step_;

        switch (currentStep) {
        case 0:
            return { 0,    0.0,   9.81, true, true };

        case 1:
            return { 500,  0.0,   9.81, true, true };

        case 2:
            return { 1000, 0.0,   18.0, true, true };

        case 3:
            return { 1500, 8.0,   17.0, true, true };

        case 4:
            return { 2000, 35.0,  14.0, true, true };

        case 5:
            return { 2500, 90.0,  10.0, true, true };

        case 6:
            return { 3000, 120.0, 9.0, true, true };

        case 7:
            return { 3500, 118.0, 9.0, true, true };

        case 8:
            return { 4000, 95.0,  9.0, true, true };

        case 9:
            return { 4500, 50.0,  9.0, true, true };

        case 10:
            return { 5000, 10.0,  9.0, true, true };

        case 11:
            return { 5500, 0.0,   9.0, true, true };

        default:
            return { 6000, 0.0,   9.0, true, true };
        }
    }

    void ScenarioGenerator::reset() {
        step_ = 0;
    }

} 