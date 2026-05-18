#pragma once

#include "core/data/TelemetryFrame.hpp"
#include "core/monitoring/SystemEvent.hpp"

#include <vector>

namespace fc {

class HealthMonitor {
public:
    HealthMonitor() = default;

    std::vector<SystemEvent> check(const TelemetryFrame& frame) const;
};

}