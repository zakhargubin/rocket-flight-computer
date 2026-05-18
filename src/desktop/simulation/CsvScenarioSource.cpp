#include "desktop/simulation/CsvScenarioSource.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fc {
    namespace {

        std::string trim(const std::string& text) {
            std::size_t begin = 0;
            while (begin < text.size() &&
                std::isspace(static_cast<unsigned char>(text[begin]))) {
                ++begin;
            }

            std::size_t end = text.size();
            while (end > begin &&
                std::isspace(static_cast<unsigned char>(text[end - 1]))) {
                --end;
            }

            return text.substr(begin, end - begin);
        }

        std::string stripBom(const std::string& text) {
            if (text.size() >= 3 &&
                static_cast<unsigned char>(text[0]) == 0xEF &&
                static_cast<unsigned char>(text[1]) == 0xBB &&
                static_cast<unsigned char>(text[2]) == 0xBF) {
                return text.substr(3);
            }

            return text;
        }

        std::vector<std::string> splitCsvLine(const std::string& line, char delimiter) {
            std::vector<std::string> result;
            std::stringstream ss(line);
            std::string item;
            bool first = true;

            while (std::getline(ss, item, delimiter)) {
                item = trim(item);

                if (first) {
                    item = stripBom(item);
                    first = false;
                }

                result.push_back(item);
            }

            return result;
        }

        int findColumnIndex(const std::vector<std::string>& header,
            const std::string& name) {
            for (std::size_t i = 0; i < header.size(); ++i) {
                if (header[i] == name) {
                    return static_cast<int>(i);
                }
            }

            return -1;
        }

        bool tryParseDouble(std::string text, double& value) {
            text = trim(text);

            if (text.empty()) {
                return false;
            }

            std::replace(text.begin(), text.end(), ',', '.');

            try {
                std::size_t pos = 0;
                value = std::stod(text, &pos);
                return pos == text.size();
            }
            catch (...) {
                return false;
            }
        }

        double synthesizeBatteryVoltage(std::uint32_t timestampMs) {
            const double seconds = static_cast<double>(timestampMs) / 1000.0;
            const double voltage = 12.3 - 0.02 * (seconds / 60.0);
            return std::max(11.8, voltage);
        }

        bool looksLikeHeader(const std::vector<std::string>& cells) {
            return findColumnIndex(cells, "Time") >= 0 &&
                findColumnIndex(cells, "Temp") >= 0 &&
                findColumnIndex(cells, "Height_K") >= 0 &&
                findColumnIndex(cells, "accel_Z") >= 0;
        }

    } // namespace

    bool CsvScenarioSource::load(const std::string& path) {
        frames_.clear();
        index_ = 0;

        std::ifstream file(path);
        if (!file.is_open()) {
            std::cout << "CsvScenarioSource: failed to open file: " << path << '\n';
            return false;
        }

        std::string line;
        std::vector<std::string> header;
        char delimiter = ',';

        while (std::getline(file, line)) {
            if (trim(line).empty()) {
                continue;
            }

            const std::vector<std::string> semicolonCells = splitCsvLine(line, ';');
            if (looksLikeHeader(semicolonCells)) {
                header = semicolonCells;
                delimiter = ';';
                break;
            }

            const std::vector<std::string> commaCells = splitCsvLine(line, ',');
            if (looksLikeHeader(commaCells)) {
                header = commaCells;
                delimiter = ',';
                break;
            }
        }

        if (header.empty()) {
            std::cout << "CsvScenarioSource: header not found\n";
            return false;
        }

        const int timeIndex = findColumnIndex(header, "Time");
        const int tempIndex = findColumnIndex(header, "Temp");
        const int altitudeIndex = findColumnIndex(header, "Height_K");
        const int accelZIndex = findColumnIndex(header, "accel_Z");

        if (timeIndex < 0 || tempIndex < 0 || altitudeIndex < 0 || accelZIndex < 0) {
            std::cout << "CsvScenarioSource: required columns not found\n";
            return false;
        }

        while (std::getline(file, line)) {
            if (trim(line).empty()) {
                continue;
            }

            const std::vector<std::string> cells = splitCsvLine(line, delimiter);
            const int requiredMaxIndex =
                std::max(std::max(timeIndex, tempIndex),
                    std::max(altitudeIndex, accelZIndex));

            if (static_cast<int>(cells.size()) <= requiredMaxIndex) {
                continue;
            }

            double rawTime = 0.0;
            double rawTemp = 0.0;
            double rawAltitude = 0.0;
            double rawAccelZ = 0.0;

            const bool timeOk = tryParseDouble(cells[timeIndex], rawTime);
            const bool tempOk = tryParseDouble(cells[tempIndex], rawTemp);
            const bool altitudeOk = tryParseDouble(cells[altitudeIndex], rawAltitude);
            const bool accelOk = tryParseDouble(cells[accelZIndex], rawAccelZ);

            if (!timeOk) {
                continue;
            }

            ScenarioFrame frame{};
            frame.timestampMs = static_cast<std::uint32_t>(rawTime);

            frame.altitude = altitudeOk ? rawAltitude : 0.0;
            frame.accelerationZ = accelOk ? -rawAccelZ : 9.81;
            frame.temperature = tempOk ? rawTemp : 0.0;
            frame.batteryVoltage = synthesizeBatteryVoltage(frame.timestampMs);

            frame.altitudeValid = altitudeOk;
            frame.imuValid = accelOk;
            frame.temperatureValid = tempOk;
            frame.batteryValid = true;

            frames_.push_back(frame);
        }

        std::cout << "CsvScenarioSource: loaded frames = " << frames_.size() << '\n';
        return !frames_.empty();
    }

    bool CsvScenarioSource::hasNext() const {
        return index_ < frames_.size();
    }

    ScenarioFrame CsvScenarioSource::next() {
        const ScenarioFrame frame = frames_[index_];
        ++index_;
        return frame;
    }

    void CsvScenarioSource::reset() {
        index_ = 0;
    }

} // namespace fc