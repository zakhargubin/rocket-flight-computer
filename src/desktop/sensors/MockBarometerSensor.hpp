#pragma once

#include "core/interfaces/Sensor.hpp"

namespace fc {

class MockBarometerSensor : public Sensor {
public:
    MockBarometerSensor() = default;

    SensorData read(const ScenarioFrame& frame) const override;
};

}