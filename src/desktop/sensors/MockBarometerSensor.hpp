#pragma once

#include "core/data/SensorData.hpp"
#include "desktop/simulation/ScenarioFrame.hpp"

namespace fc {

    class MockBarometerSensor {
    public:
        MockBarometerSensor() = default;

        SensorData read(const ScenarioFrame& frame) const;
    };

}