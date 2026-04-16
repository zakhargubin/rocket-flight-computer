#pragma once

#include "core/SensorData.hpp"

#include <cstdint>
#include <string>

namespace fc {

class Sensor {
public:
    explicit Sensor(std::string name);
    virtual ~Sensor() = default;

    virtual bool init() = 0;
    virtual SensorData read(std::uint64_t timestamp_ms) = 0;
    virtual SensorKind kind() const = 0;

    const std::string& name() const;
    bool isInitialized() const;
    bool isHealthy() const;

protected:
    void setInitialized(bool value);
    void setHealthy(bool value);

private:
    std::string name_;
    bool initialized_ {false};
    bool healthy_ {true};
};

} // namespace fc
