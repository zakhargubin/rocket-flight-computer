#pragma once

#include "core/FlightStateMachine.hpp"
#include "core/Logger.hpp"
#include "core/Sensor.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace fc {

class FlightComputer {
public:
    FlightComputer(Logger& logger, FlightStateMachine& state_machine);

    void addSensor(std::unique_ptr<Sensor> sensor);
    bool initSensors();
    void run(std::uint64_t step_ms, std::size_t step_count);

private:
    void processData(const SensorData& data);
    void printStep(const FlightSnapshot& snapshot, std::uint64_t timestamp_ms) const;

    Logger& logger_;
    FlightStateMachine& state_machine_;
    std::vector<std::unique_ptr<Sensor>> sensors_;
    FlightSnapshot snapshot_ {};
};

} // namespace fc
