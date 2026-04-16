#include "core/Sensor.hpp"

namespace fc {

Sensor::Sensor(std::string name)
    : name_(std::move(name)) {
}

const std::string& Sensor::name() const {
    return name_;
}

bool Sensor::isInitialized() const {
    return initialized_;
}

bool Sensor::isHealthy() const {
    return healthy_;
}

void Sensor::setInitialized(bool value) {
    initialized_ = value;
}

void Sensor::setHealthy(bool value) {
    healthy_ = value;
}

} // namespace fc
