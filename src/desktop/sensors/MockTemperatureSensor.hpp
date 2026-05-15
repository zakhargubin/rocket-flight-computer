#pragma once

#include "core/interfaces/Sensor.hpp"

namespace fc {

class MockTemperatureSensor : public Sensor {
public:
    MockTemperatureSensor() = default;

    SensorData read(const ScenarioFrame& frame) const override;
};

}