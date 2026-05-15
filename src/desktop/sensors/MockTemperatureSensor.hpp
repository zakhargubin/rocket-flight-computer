#pragma once

#include "core/data/SensorData.hpp"
#include "desktop/simulation/ScenarioFrame.hpp"

namespace fc {

    class MockTemperatureSensor {
    public:
        MockTemperatureSensor() = default;

        SensorData read(const ScenarioFrame& frame) const;
    };

}