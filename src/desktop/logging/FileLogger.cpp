#include "desktop/logging/FileLogger.hpp"

namespace fc {

FileLogger::~FileLogger() {
    close();
}

bool FileLogger::open(const std::string& path) {
    file_.open(path);
    return file_.is_open();
}

void FileLogger::logFrame(const TelemetryFrame& frame, FlightState state) {
    if (!file_.is_open()) {
        return;
    }

    file_
        << "t = " << frame.timestampMs << " ms"
        << ", altitude = " << frame.altitude
        << ", az = " << frame.accelerationZ
        << ", state = " << toString(state)
        << '\n';
}

void FileLogger::logMessage(const std::string& message) {
    if (!file_.is_open()) {
        return;
    }

    file_ << message << '\n';
}

void FileLogger::close() {
    if (file_.is_open()) {
        file_.close();
    }
}

}