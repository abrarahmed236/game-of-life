#include "game_of_life.h"

gol::GameOfLife::GameOfLife() {
    total_ticks = 3000;
    TICK_LENGTH = 300000;
    // Move above lines over to the calling program code

    SIZE = 56;
    I = SIZE;
    J = 180;
    std::vector<int> temp(J);
    space.assign(I, temp);
    space_1 = space;
    I = space.size();
    J = space[0].size();
    outstr = "";
    outstr.reserve(38600);
}

void gol::GameOfLife::Init() {
    srand(time(NULL));
    for (int i = I / 20; i <= 19 * I / 20; i++) {
        for (int j = J / 40; j <= 39 * J / 40; j++) {
            space[i][j] = (rand() % (4) == 0 ? 1 : 0);
        }
    }
}

void gol::GameOfLife::Render(int tick) {
    outstr = "\t\t\t\t\t\t\t*****     tick : " + std::to_string(tick) +
             "      *****\t\t\t\t\t\t\t\n\n" + shitstr();

    for (int i = 0; i < I; i++) {
        outstr.push_back(' ');
        outstr.push_back(' ');
        outstr.push_back(' ');
        outstr.push_back(' ');
        outstr.push_back('|');
        for (int j = 0; j < J; j++) {
            outstr.push_back(space[i][j] ? '0' : ' ');
        }
        outstr.push_back('|');
        outstr.push_back('\n');
    }
    outstr += shitstr();
    std::cout << outstr << std::endl;
    outstr.resize(0);
    // cout << outstr.capacity() << endl;
}

void gol::GameOfLife::Update() {
    for (int i = 0; i < I; i++) {
        for (int j = 0; j < J; j++) {
            int numCells = getCells(i, j);
            space_1[i][j] =
                (numCells == 3 || (numCells == 2 && space[i][j])) ? 1 : 0;
        }
    }
    space.swap(space_1);
}

void gol::GameOfLife::Over() {
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "                                                  ";
    std::cout << "                                                  ";
    std::cout << " Game Over";
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int gol::GameOfLife::getCells(int i, int j) {
    int result = 0;
    result += space[(i - 1 + I) % I][(j - 1 + J) % J];
    result += space[(i - 1 + I) % I][j];
    result += space[(i - 1 + I) % I][(j + 1) % J];
    result += space[i][(j - 1 + J) % J];
    result += space[i][(j + 1) % J];
    result += space[(i + 1) % I][(j - 1 + J) % J];
    result += space[(i + 1) % I][j];
    result += space[(i + 1) % I][(j + 1) % J];
    return result;
}

std::string gol::GameOfLife::shitstr() {
    std::string result = "    ";
    for (int i = 0; i < J + 2; i++) {
        result.push_back('-');
    }
    result.push_back('\n');
    return result;
}
