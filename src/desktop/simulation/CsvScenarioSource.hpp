#pragma once

#include "core/interfaces/ScenarioSource.hpp"

#include <string>
#include <vector>

namespace fc {

class CsvScenarioSource : public ScenarioSource {
private:
	std::vector<ScenarioFrame> frames_{};
	std::size_t index_{ 0 };
public:
	CsvScenarioSource() = default;

	bool load(const std::string& path);
	bool hasNext() const override;
	ScenarioFrame next() override;
	void reset() override;
};

}