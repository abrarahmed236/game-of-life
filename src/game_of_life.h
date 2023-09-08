#ifndef Game_Of_Life
#define Game_Of_Life

#include <fcntl.h>      // for keypress
#include <sys/ioctl.h>  // for tty size
#include <termios.h>    // for tc_attributes
#include <unistd.h>     // for usleep() function

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace gol {

class GameOfLife {
   private:
    bool paused, running;
    int rows, cols;
    int row_pad, col_pad;
    int tick, total_ticks, tick_length;
    std::vector<std::vector<int>> space;
    std::vector<std::vector<int>> space_aux;
    std::string outstr;

    void Render(int tick);
    void Update();
    void Over(std::string splash_string);

    void TogglePause();

    int GetTTYrows();
    int GetTTYcols();
    int GetCells(int i, int j);
    bool KeyPressed();
    std::string divider();

   public:
    GameOfLife(int total_ticks_in, int tick_length_in);
    void Init();
    void Run();
};

}  // namespace gol

#endif