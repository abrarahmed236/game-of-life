#include "game_of_life.h"

gol::GameOfLife::GameOfLife(int total_ticks_in, int tick_length_in) {
    total_ticks = total_ticks_in;
    tick_length = tick_length_in;
    row_pad = 6;
    col_pad = 10;
}

void gol::GameOfLife::Init() {
    rows = getSize(0) - row_pad;
    cols = getSize(1) - col_pad;
    space.assign(rows, std::vector<int>(cols));
    space_aux = space;
    outstr = "";
    // outstr.reserve(38600);

    srand(time(NULL));
    for (int i = rows / 20; i <= 19 * rows / 20; i++) {
        for (int j = cols / 40; j <= 39 * cols / 40; j++) {
            space[i][j] = (rand() % (4) == 0 ? 1 : 0);
        }
    }
}

void gol::GameOfLife::Run() {
    while (1) {
        Init();
        Render(0);
        usleep(3000000);
        for (tick = 0; tick < total_ticks; tick++) {
            Update();
            Render(tick);
            usleep(tick_length);
        }
        Over();
        usleep(3000000);
    }
}

void gol::GameOfLife::Render(int tick) {
    int width = getSize(1);
    std::string tick_str = std::to_string(tick);
    int pad = std::max(0, 6 - static_cast<int>(tick_str.size()));
    std::string padding(pad, ' ');
    std::string trailer =
        "*****     tick : " + padding + tick_str + "      *****\n";

    outstr = "\n" + std::string((width - trailer.size()) / 2, ' ');
    outstr += trailer;

    outstr += divider();
    for (int i = 0; i < rows; i++) {
        outstr.push_back(' ');
        outstr.push_back(' ');
        outstr.push_back(' ');
        outstr.push_back(' ');
        outstr.push_back('|');
        for (int j = 0; j < cols; j++) {
            outstr.push_back(space[i][j] ? '0' : ' ');
        }
        outstr.push_back('|');
        outstr.push_back('\n');
    }
    outstr += divider();
    std::cout << outstr << std::endl;
    // outstr.resize(0);
}

void gol::GameOfLife::Update() {
    if (rows != getSize(0) - row_pad || cols != getSize(1) - col_pad) {
        // force game over
        tick = total_ticks;
    }
    for (int i = 0; i < rows && i < space_aux.size(); i++) {
        for (int j = 0; j < cols && j < space_aux[0].size(); j++) {
            int numCells = getCells(i, j);
            space_aux[i][j] =
                (numCells == 3 || (numCells == 2 && space[i][j])) ? 1 : 0;
        }
    }
    space.swap(space_aux);
}

void gol::GameOfLife::Over() {
    int height = getSize(0);
    int width = getSize(1);
    std::string padding((width - 10) / 2, ' ');
    outstr = std::string(height / 2 - 1, '\n');
    outstr += padding + "Game Over";
    outstr += std::string(height / 2 - 1, '\n');
    std::cout << outstr << std::endl;
}

int gol::GameOfLife::getSize(int x) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    if (x == 0)  // x == 0 indicates rows
        return w.ws_row;
    else  // x == 1 indcates columns
        return w.ws_col;
}

int gol::GameOfLife::getCells(int i, int j) {
    int result = 0;
    result += space[(i - 1 + rows) % rows][(j - 1 + cols) % cols];
    result += space[(i - 1 + rows) % rows][j];
    result += space[(i - 1 + rows) % rows][(j + 1) % cols];
    result += space[i][(j - 1 + cols) % cols];
    result += space[i][(j + 1) % cols];
    result += space[(i + 1) % rows][(j - 1 + cols) % cols];
    result += space[(i + 1) % rows][j];
    result += space[(i + 1) % rows][(j + 1) % cols];
    return result;
}

std::string gol::GameOfLife::divider() {
    std::string result = "    ";
    for (int i = 0; i < cols + 2; i++) {
        result.push_back('-');
    }
    result.push_back('\n');
    return result;
}
