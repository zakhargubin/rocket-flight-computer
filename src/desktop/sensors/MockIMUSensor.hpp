#pragma once

#include "core/data/SensorData.hpp"
#include "desktop/simulation/ScenarioFrame.hpp"

namespace fc {

    class MockIMUSensor {
    public:
        MockIMUSensor() = default;

        SensorData read(const ScenarioFrame& frame) const;
    };

} 