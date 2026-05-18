#pragma once

#include "desktop/simulation/ScenarioFrame.hpp"

namespace fc {

class ScenarioSource {
public:
	virtual ~ScenarioSource() = default;
	virtual bool hasNext() const = 0;
	virtual ScenarioFrame next() = 0;
	virtual void reset() = 0;
};

}