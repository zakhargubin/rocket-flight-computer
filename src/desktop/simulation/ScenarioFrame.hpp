#pragma once

#include <cstdint>

namespace fc {
struct ScenarioFrame {
	std::uint32_t timestampMs {0};

	double altitude{ 0.0 };
	double accelerationZ {9.81};
	
	bool altitudeValid{ false };
	bool imuValid{ false };

};

}