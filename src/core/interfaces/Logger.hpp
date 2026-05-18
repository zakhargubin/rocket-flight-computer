#pragma once

#include "core/data/TelemetryFrame.hpp"
#include "core/flight/FlightState.hpp"

#include <string>

namespace fc {

class Logger {
public:
	virtual ~Logger() = default;

	virtual bool open(const std::string& path) = 0;
	virtual void logFrame(const TelemetryFrame& frame, FlightState state) = 0;
	virtual void logMessage(const std::string& message) = 0;
	virtual void close() = 0;
};
}