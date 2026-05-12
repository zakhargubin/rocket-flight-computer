#pragma once

#include "core/data/SensorData.hpp"
#include "core/data/TelemetryFrame.hpp"

namespace fc {

    class DataAggregator {
    public:
        DataAggregator() = default;

        void reset();
        void add(const SensorData& data);
        TelemetryFrame buildFrame() const;

    private:
        TelemetryFrame frame_{};
    };

} // namespace fc