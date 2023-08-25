#ifndef Game_Of_Life
#define Game_Of_Life

#include <sys/ioctl.h> // for tty size
#include <unistd.h>  // for usleep() function

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace gol {

class GameOfLife {
   private:
    int rows, cols, SIZE;
    int tick, total_ticks, tick_length;
    std::vector<std::vector<int>> space;
    std::vector<std::vector<int>> space_aux;
    std::string outstr;

    void Render(int tick);
    void Update();
    void Over();

    int getSize(int x);
    int getCells(int i, int j);
    std::string divider();

   public:
    GameOfLife(int total_ticks_in, int tick_length_in);
    void Init();
    void Run();
};

}  // namespace gol

#endif