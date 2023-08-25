#include "game_of_life.h"

int main() {
    gol::GameOfLife game;
    while (1) {
        game.Init();

        game.tick = 0;
        for (; game.tick < 10; game.tick++) {
            game.Render(game.tick);
            usleep(game.TICK_LENGTH);
        }
        for (; game.tick < game.total_ticks; game.tick++) {
            game.Update();
            game.Render(game.tick);
            usleep(game.TICK_LENGTH);
        }

        game.Over();
    }

    return 0;
}