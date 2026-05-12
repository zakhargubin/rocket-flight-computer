#include "core/services/DataAggregator.hpp"

namespace fc {

    void DataAggregator::reset() {
        frame_ = {};
    }

    void DataAggregator::add(const SensorData& data) {
        frame_.timestampMs = data.timestampMs;

        switch (data.kind) {
        case SensorKind::IMU:
            frame_.accelerationZ = data.value1;
            frame_.imuValid = data.valid;
            break;

        case SensorKind::Barometer:
            frame_.altitude = data.value1;
            frame_.altitudeValid = data.valid;
            break;
        }
    }

    TelemetryFrame DataAggregator::buildFrame() const {
        return frame_;
    }

}