#include "desktop/app/DesktopFlightComputer.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace fc {
    namespace {

        std::vector<std::filesystem::path> collectCsvPaths(const std::string& directory) {
            std::vector<std::filesystem::path> result;

            const std::filesystem::path dirPath(directory);
            if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath)) {
                return result;
            }

            for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
                if (!entry.is_regular_file()) {
                    continue;
                }

                if (entry.path().extension() == ".csv") {
                    result.push_back(entry.path());
                }
            }

            std::sort(result.begin(), result.end());
            return result;
        }

        int readMenuChoice(int minValue, int maxValue) {
            while (true) {
                std::cout << "\nEnter choice [" << minValue << "-" << maxValue << "]: ";

                int choice = 0;
                if (std::cin >> choice && choice >= minValue && choice <= maxValue) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return choice;
                }

                std::cout << "Invalid input. Try again.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

    } // namespace

    bool DesktopFlightComputer::init() {
        sensors_.push_back(&imu_);
        sensors_.push_back(&barometer_);
        sensors_.push_back(&temperature_);
        sensors_.push_back(&battery_);

        logger_ = &fileLogger_;

        if (!selectScenarioSource()) {
            return false;
        }

        std::string playbackModeMessage;

        std::cout << "\nPlayback mode:\n";
        std::cout << "1. Fast\n";
        std::cout << "2. Real-time x1\n";
        std::cout << "3. Real-time x5\n";

        const int playbackChoice = readMenuChoice(1, 3);

        switch (playbackChoice) {
        case 1:
            replayController_.configure(PlaybackMode::Fast, 1.0);
            playbackModeMessage = "Playback mode: Fast";
            break;

        case 2:
            replayController_.configure(PlaybackMode::RealTime, 1.0);
            playbackModeMessage = "Playback mode: Real-time x1";
            break;

        case 3:
            replayController_.configure(PlaybackMode::RealTime, 5.0);
            playbackModeMessage = "Playback mode: Real-time x5";
            break;

        default:
            replayController_.configure(PlaybackMode::Fast, 1.0);
            playbackModeMessage = "Playback mode: Fast";
            break;
        }

        if (!logger_->open("flight_log.txt")) {
            return false;
        }

        logger_->logMessage(playbackModeMessage);
        logger_->logMessage("Flight log started");
        return true;
    }

    void DesktopFlightComputer::useBuiltInScenario() {
        builtInScenario_.reset();
        scenarioSource_ = &builtInScenario_;
    }

    bool DesktopFlightComputer::tryLoadCsvScenario(const std::string& path) {
        if (!csvScenario_.load(path)) {
            return false;
        }

        csvScenario_.reset();
        scenarioSource_ = &csvScenario_;
        return true;
    }

    bool DesktopFlightComputer::selectScenarioSource() {
        const std::vector<std::filesystem::path> csvPaths = collectCsvPaths("scenarios");

        while (true) {
            std::cout << "\n========================================\n";
            std::cout << " Rocket Flight Computer - Scenario Menu\n";
            std::cout << "========================================\n";
            std::cout << "1. Built-in demo scenario\n";

            for (std::size_t i = 0; i < csvPaths.size(); ++i) {
                std::cout << (i + 2) << ". CSV: " << csvPaths[i].filename().string() << '\n';
            }

            std::cout << "0. Exit\n";

            const int choice = readMenuChoice(0, static_cast<int>(csvPaths.size()) + 1);

            if (choice == 0) {
                std::cout << "Exit selected.\n";
                return false;
            }

            if (choice == 1) {
                useBuiltInScenario();
                std::cout << "Using built-in scenario.\n";
                return true;
            }

            const std::filesystem::path& selectedPath = csvPaths[static_cast<std::size_t>(choice - 2)];
            if (tryLoadCsvScenario(selectedPath.string())) {
                std::cout << "Loaded CSV scenario: " << selectedPath.filename().string() << '\n';
                return true;
            }

            std::cout << "Failed to load CSV scenario: "
                << selectedPath.filename().string()
                << "\nChoose another option.\n";
        }
    }

    void DesktopFlightComputer::run() {
        replayController_.reset();

        while (scenarioSource_->hasNext()) {
            const ScenarioFrame scenarioFrame = scenarioSource_->next();
            replayController_.syncToTimestamp(scenarioFrame.timestampMs);

            aggregator_.reset();

            for (const Sensor* sensor : sensors_) {
                aggregator_.add(sensor->read(scenarioFrame));
            }

            const TelemetryFrame frame = aggregator_.buildFrame();
            const FlightState state = machine_.update(frame);

            const std::vector<SystemEvent> events = healthMonitor_.check(frame);

            std::cout
                << "t = " << frame.timestampMs << " ms"
                << ", altitude = " << frame.altitude
                << ", az = " << frame.accelerationZ
                << ", temperature = " << frame.temperature
                << ", battery = " << frame.batteryVoltage
                << ", state = " << toString(state)
                << '\n';

            logger_->logFrame(frame, state);

            for (const SystemEvent& event : events) {
                const std::string message =
                    std::string("[") + toString(event.severity) + "] "
                    + toString(event.code)
                    + " at t = " + std::to_string(event.timestampMs) + " ms";

                std::cout << message << '\n';
                logger_->logMessage(message);
            }
        }

        logger_->logMessage("Flight log finished");
        logger_->close();
    }

} // namespace fc