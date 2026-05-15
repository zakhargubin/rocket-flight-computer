#pragma once

#include "core/interfaces/Sensor.hpp"

namespace fc {

class MockBatterySensor : public Sensor {
public:
    MockBatterySensor() = default;

    SensorData read(const ScenarioFrame& frame) const override;
};

}