#include "desktop/app/DesktopFlightComputer.hpp"

#include <iostream>

int main() {
    fc::DesktopFlightComputer computer;

    if (!computer.init()) {
        std::cerr << "Failed to initialize DesktopFlightComputer\n";
        return 1;
    }

    computer.run();
    return 0;
}