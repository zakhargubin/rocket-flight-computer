#pragma once

#include "core/Sensor.hpp"
#include "simulation/ScenarioGenerator.hpp"

namespace fc {

class IMUSensor final : public Sensor {
public:
    explicit IMUSensor(const ScenarioGenerator& scenario);

    bool init() override;
    SensorData read(std::uint64_t timestamp_ms) override;
    SensorKind kind() const override;

private:
    const ScenarioGenerator& scenario_;
};

} // namespace fc
