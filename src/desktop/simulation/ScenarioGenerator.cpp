#include "desktop/simulation/ScenarioGenerator.hpp"

namespace fc {

    bool ScenarioGenerator::hasNext() const {
        return step_ < maxSteps_;
    }

    ScenarioFrame ScenarioGenerator::next() {
        const std::uint32_t currentStep = step_;
        ++step_;

        switch (currentStep) {
        case 0:
            return { 0,    0.0,   9.81, 20.0, 12.6, true, true, true, true };

        case 1:
            return { 500,  0.0,   9.81, 20.1, 12.5, true, true, true, true };

        case 2:
            return { 1000, 0.0,   18.0, 20.3, 12.5, true, true, true, true };

        case 3:
            return { 1500, 8.0,   17.0, 20.5, 12.4, true, true, true, true };

        case 4:
            return { 2000, 35.0,  14.0, 20.8, 12.4, true, true, true, true };

        case 5:
            return { 2500, 90.0,  10.0, 21.2, 12.3, true, true, true, true };

        case 6:
            return { 3000, 120.0, 9.0,  21.6, 12.2, true, true, true, true };

        case 7:
            return { 3500, 118.0, 9.0,  22.0, 12.1, true, true, true, true };

        case 8:
            return { 4000, 95.0,  9.0,  22.3, 12.1, true, true, true, true };

        case 9:
            return { 4500, 50.0,  9.0,  22.6, 12.0, true, true, true, true };

        case 10:
            return { 5000, 10.0, 9.0, 62.0, 10.8, true, true, true, true };

        case 11:
            return { 5500, 0.0, 9.0, 65.0, 10.3, true, true, true, true };

        default:
            return { 6000, 0.0,   9.0,  23.0, 11.8, true, true, true, true };
        }
    }

    void ScenarioGenerator::reset() {
        step_ = 0;
    }

}