#include "game_of_life.h"

std::string gol::GameOfLife::divider() {
    std::string result = "    ";
    for (int i = 0; i < cols + 2; i++) {
        result.push_back('-');
    }
    result.push_back('\n');
    return result;
}