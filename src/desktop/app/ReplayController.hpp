#pragma once

#include <chrono>
#include <cstdint>

namespace fc {

enum class PlaybackMode {
    Fast,
    RealTime
};

class ReplayController {
public:
    ReplayController() = default;

    void configure(PlaybackMode mode, double speed = 1.0);
    void reset();
    void syncToTimestamp(std::uint32_t timestampMs);

private:
    PlaybackMode mode_{ PlaybackMode::Fast };
    double speed_{ 1.0 };

    bool started_{ false };
    std::uint32_t firstTimestampMs_{ 0 };
    std::chrono::steady_clock::time_point wallStart_{};
};

}