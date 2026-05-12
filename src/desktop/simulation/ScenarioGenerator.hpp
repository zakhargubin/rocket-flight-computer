#pragma once

#include "core/data/TelemetryFrame.hpp"
#include "ScenarioFrame.hpp"
#include <cstdint>

namespace fc {

class ScenarioGenerator{
private:
	std::uint32_t step_ {0};
	static constexpr std::uint32_t maxSteps_{ 12 };
public:
	ScenarioGenerator() = default;

	bool hasNext() const;
	ScenarioFrame next();
	void reset();
};

}