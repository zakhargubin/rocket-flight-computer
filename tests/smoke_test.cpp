#include "core/FlightStateMachine.hpp"
#include "sensors/BarometerSensor.hpp"
#include "sensors/IMUSensor.hpp"
#include "simulation/ScenarioGenerator.hpp"

#include <cassert>
#include <cstdint>

int main() {
    fc::ScenarioGenerator scenario;
    fc::IMUSensor imu(scenario);
    fc::BarometerSensor baro(scenario);

    assert(imu.init());
    assert(baro.init());

    const fc::SensorData imu_data = imu.read(2500);
    const fc::SensorData baro_data = baro.read(2500);

    assert(imu_data.value_count == 2U);
    assert(baro_data.value_count == 1U);
    assert(imu_data.values[0] > 15.0);
    assert(baro_data.values[0] > 0.0);

    fc::FlightStateMachine machine;
    fc::FlightSnapshot snapshot {};

    const std::uint64_t timeline_ms[] = {0, 2500, 4000, 8500, 10500, 18500, 19000};

    for (const auto timestamp_ms : timeline_ms) {
        const auto imu_frame = imu.read(timestamp_ms);
        const auto baro_frame = baro.read(timestamp_ms);

        snapshot.has_acceleration = true;
        snapshot.acceleration_z_mps2 = imu_frame.values[0];
        snapshot.has_altitude = true;
        snapshot.altitude_m = baro_frame.values[0];

        machine.update(snapshot);
    }

    assert(machine.state() == fc::FlightState::Landed);
    return 0;
}
