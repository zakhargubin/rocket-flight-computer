#pragma once

#include "core/data/TelemetryFrame.hpp"
#include "core/flight/FlightState.hpp"

#include <fstream>
#include <string>

namespace fc {

class FileLogger {
private:
    std::ofstream file_;
public:
    FileLogger() = default;
    ~FileLogger();

    bool open(const std::string& path);
    void logFrame(const TelemetryFrame& frame, FlightState state);
    void logMessage(const std::string& message);
    void close();

};

} // namespace fc