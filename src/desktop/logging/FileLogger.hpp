#pragma once

#include "core/interfaces/Logger.hpp"

#include <fstream>
#include <string>

namespace fc {

class FileLogger : public Logger {
private:
    std::ofstream file_;
public:
    FileLogger() = default;
    ~FileLogger();

    bool open(const std::string& path) override;
    void logFrame(const TelemetryFrame& frame, FlightState state) override;
    void logMessage(const std::string& message) override;
    void close() override;

};
}