#include "gui/gui.h"
#include "precompute.h"
#include <sstream>

int main() {

    initPrecompute();

    initBook();

    std::string input;
    while (getline(std::cin, input)) {
        stringstream ss(input);
        std::string command;
        ss >> command;
        if (command == "gui") {
            ss >> command;
            if (command != "gui") {
                loop(input.substr(input.find('g') + 4));
            }
            loop("startpos");
        } else if (command == "uci") {
            uci();
        }
    }

    return 0;
}