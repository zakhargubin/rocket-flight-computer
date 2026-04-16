#include "core/Logger.hpp"

#include <iomanip>
#include <sstream>

namespace fc {

Logger::~Logger() {
    close();
}

bool Logger::open(const std::string& file_name) {
    close();
    file_.open(file_name);
    return file_.is_open();
}

void Logger::close() {
    if (file_.is_open()) {
        file_.close();
    }
}

bool Logger::isOpen() const {
    return file_.is_open();
}

void Logger::logMessage(const std::string& message) {
    if (!isOpen()) {
        return;
    }

    file_ << "[MSG] " << message << '\n';
}

void Logger::logData(const SensorData& data) {
    if (!isOpen()) {
        return;
    }

    file_ << "[DATA] "
          << "t=" << data.timestamp_ms << " ms"
          << ", sensor=" << data.sensor_name
          << ", status=" << statusToString(data.status)
          << ", values=";

    for (std::size_t i = 0; i < data.value_count; ++i) {
        file_ << std::fixed << std::setprecision(2) << data.values[i];
        if (i + 1U != data.value_count) {
            file_ << ", ";
        }
    }

    if (!data.note.empty()) {
        file_ << ", note=" << data.note;
    }

    file_ << '\n';
}

std::string Logger::statusToString(ReadStatus status) {
    switch (status) {
    case ReadStatus::Ok:
        return "ok";
    case ReadStatus::Warning:
        return "warning";
    case ReadStatus::Error:
        return "error";
    }

    return "unknown";
}

} // namespace fc
