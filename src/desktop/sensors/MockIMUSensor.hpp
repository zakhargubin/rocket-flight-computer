#pragma once

#include "core/interfaces/Sensor.hpp"

namespace fc {

class MockIMUSensor : public Sensor {
public:
    MockIMUSensor() = default;

    SensorData read(const ScenarioFrame& frame) const override;
};

}