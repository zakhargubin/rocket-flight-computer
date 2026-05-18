#pragma once

#include "core/interfaces/ScenarioSource.hpp"

#include <cstdint>

namespace fc {

class ScenarioGenerator : public ScenarioSource {
private:
    std::uint32_t step_{ 0 };
    static constexpr std::uint32_t maxSteps_{ 12 };
public:
    ScenarioGenerator() = default;

    bool hasNext() const override;
    ScenarioFrame next() override;
    void reset() override;

};

}