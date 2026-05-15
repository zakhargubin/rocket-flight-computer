#pragma once

#include "core/data/SensorData.hpp"
#include "desktop/simulation/ScenarioFrame.hpp"

namespace fc {

class Sensor {
public:
    virtual ~Sensor() = default;

    virtual SensorData read(const ScenarioFrame& frame) const = 0;
};

}