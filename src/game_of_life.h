#ifndef Game_Of_Life
#define Game_Of_Life

#include <unistd.h>  // for sleep() function

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace gol {

class GameOfLife {
   private:
    int I, J, SIZE;
    std::vector<std::vector<int>> space;
    std::vector<std::vector<int>> space_1;
    std::string outstr;

   public:
    int tick, total_ticks;
    int TICK_LENGTH;
    GameOfLife();
    void Init();
    void Render(int tick);
    void Update();
    void Over();
    int getCells(int i, int j);
    std::string shitstr();
};

}  // namespace gol

#endif