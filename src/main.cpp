#include "game_of_life.h"

int main() {
    int total_ticks = 1000;
    int tick_length = 100000;
    gol::GameOfLife game(total_ticks, tick_length);
    game.Run();

    return 0;
}