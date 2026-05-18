#include "desktop/app/ReplayController.hpp"

#include <thread>

namespace fc {

    void ReplayController::configure(PlaybackMode mode, double speed) {
        mode_ = mode;
        speed_ = (speed > 0.0) ? speed : 1.0;
    }

    void ReplayController::reset() {
        started_ = false;
        firstTimestampMs_ = 0;
        wallStart_ = std::chrono::steady_clock::time_point{};
    }

    void ReplayController::syncToTimestamp(std::uint32_t timestampMs) {
        if (mode_ == PlaybackMode::Fast) {
            return;
        }

        if (!started_) {
            started_ = true;
            firstTimestampMs_ = timestampMs;
            wallStart_ = std::chrono::steady_clock::now();
            return;
        }

        if (timestampMs < firstTimestampMs_) {
            timestampMs = firstTimestampMs_;
        }

        const std::uint32_t scenarioDeltaMs = timestampMs - firstTimestampMs_;

        const auto scaledDelta =
            std::chrono::duration<double, std::milli>(
                static_cast<double>(scenarioDeltaMs) / speed_
            );

        const auto targetTime =
            wallStart_ + std::chrono::duration_cast<std::chrono::steady_clock::duration>(scaledDelta);

        std::this_thread::sleep_until(targetTime);
    }

}