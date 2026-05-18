#pragma once

#include "core/flight/FlightStateMachine.hpp"
#include "core/interfaces/Logger.hpp"
#include "core/interfaces/ScenarioSource.hpp"
#include "core/interfaces/Sensor.hpp"
#include "core/monitoring/HealthMonitor.hpp"
#include "core/services/DataAggregator.hpp"
#include "desktop/app/ReplayController.hpp"
#include "desktop/logging/FileLogger.hpp"
#include "desktop/sensors/MockBarometerSensor.hpp"
#include "desktop/sensors/MockBatterySensor.hpp"
#include "desktop/sensors/MockIMUSensor.hpp"
#include "desktop/sensors/MockTemperatureSensor.hpp"
#include "desktop/simulation/CsvScenarioSource.hpp"
#include "desktop/simulation/ScenarioGenerator.hpp"

#include <string>
#include <vector>

namespace fc {

    class DesktopFlightComputer {
    public:
        DesktopFlightComputer() = default;

        bool init();
        void run();

    private:
        bool selectScenarioSource();
        bool tryLoadCsvScenario(const std::string& path);
        void useBuiltInScenario();
        ScenarioGenerator builtInScenario_{};
        CsvScenarioSource csvScenario_{};
        ScenarioSource* scenarioSource_{ nullptr };
        ReplayController replayController_{};

        MockIMUSensor imu_{};
        MockBarometerSensor barometer_{};
        MockTemperatureSensor temperature_{};
        MockBatterySensor battery_{};

        std::vector<const Sensor*> sensors_{};

        FileLogger fileLogger_{};
        Logger* logger_{ nullptr };

        DataAggregator aggregator_{};
        FlightStateMachine machine_{};
        HealthMonitor healthMonitor_{};
    };

}