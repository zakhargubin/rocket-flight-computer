#pragma once

#include "core/data/SensorData.hpp"
#include "desktop/simulation/ScenarioFrame.hpp"

namespace fc {

    class MockBatterySensor {
    public:
        MockBatterySensor() = default;

        SensorData read(const ScenarioFrame& frame) const;
    };

}