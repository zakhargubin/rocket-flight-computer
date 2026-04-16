#pragma once

#include "core/SensorData.hpp"

#include <fstream>
#include <string>

namespace fc {

class Logger {
public:
    Logger() = default;
    ~Logger();

    bool open(const std::string& file_name);
    void close();
    bool isOpen() const;

    void logMessage(const std::string& message);
    void logData(const SensorData& data);

private:
    static std::string statusToString(ReadStatus status);

    std::ofstream file_;
};

} // namespace fc
