#include "core/FlightComputer.hpp"

#include <iostream>

namespace fc {

FlightComputer::FlightComputer(Logger& logger, FlightStateMachine& state_machine)
    : logger_(logger), state_machine_(state_machine) {
}

void FlightComputer::addSensor(std::unique_ptr<Sensor> sensor) {
    sensors_.push_back(std::move(sensor));
}

bool FlightComputer::initSensors() {
    bool all_ok = true;

    for (const auto& sensor : sensors_) {
        if (!sensor->init()) {
            all_ok = false;
            logger_.logMessage("Failed to initialize sensor: " + sensor->name());
        } else {
            logger_.logMessage("Initialized sensor: " + sensor->name());
        }
    }

    return all_ok;
}

void FlightComputer::run(std::uint64_t step_ms, std::size_t step_count) {
    for (std::size_t step = 0; step < step_count; ++step) {
        const std::uint64_t timestamp_ms = step_ms * step;

        for (const auto& sensor : sensors_) {
            const SensorData data = sensor->read(timestamp_ms);
            logger_.logData(data);
            processData(data);
        }

        if (state_machine_.update(snapshot_)) {
            logger_.logMessage("Flight state changed to: " + state_machine_.stateName());
        }

        printStep(snapshot_, timestamp_ms);
    }
}

void FlightComputer::processData(const SensorData& data) {
    if (data.kind == SensorKind::Barometer && data.value_count >= 1U) {
        snapshot_.has_altitude = true;
        snapshot_.altitude_m = data.values[0];
    }

    if (data.kind == SensorKind::IMU && data.value_count >= 1U) {
        snapshot_.has_acceleration = true;
        snapshot_.acceleration_z_mps2 = data.values[0];
    }
}

void FlightComputer::printStep(const FlightSnapshot& snapshot, std::uint64_t timestamp_ms) const {
    std::cout << "t=" << timestamp_ms << " ms"
              << " | state=" << state_machine_.stateName();

    if (snapshot.has_altitude) {
        std::cout << " | altitude=" << snapshot.altitude_m << " m";
    }

    if (snapshot.has_acceleration) {
        std::cout << " | az=" << snapshot.acceleration_z_mps2 << " m/s^2";
    }

    std::cout << '\n';
}

} // namespace fc
