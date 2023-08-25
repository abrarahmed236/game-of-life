#include <unistd.h>  // for sleep() function

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int I, J, SIZE;
int total_ticks = 3000;
int TICK_LENGTH = 100000;
vector<vector<int>> space;
vector<vector<int>> space_1;
string outstr;

void Construct();
void Initialize();
void Render(int tick);
void Update();
void Over();
int getCells(int i, int j);
string shitstr();

int main() {
    while (1) {
        Construct();
        Initialize();

        int tick = 0;
        for (; tick < 30; tick++) {
            Render(tick);
            usleep(TICK_LENGTH);
        }
        for (; tick < total_ticks; tick++) {
            Update();
            Render(tick);
            usleep(TICK_LENGTH);
        }

        Over();
    }

    return 0;
}

void Construct() {
    SIZE = 87;
    I = SIZE;
    J = 445;
    vector<int> temp(J);
    space.assign(I, temp);
    space_1 = space;
    I = space.size();
    J = space[0].size();
    outstr = "";
    outstr.reserve(38600);
}

void Initialize() {
    srand(time(NULL));
    for (int i = I / 20; i <= 19 * I / 20; i++) {
        for (int j = J / 40; j <= 39 * J / 40; j++) {
            space[i][j] = (rand() % (4) == 0 ? 1 : 0);
        }
    }
}

void Render(int tick) {
    outstr = "\t\t\t\t\t\t\t*****     tick : " + to_string(tick) +
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
    cout << outstr << endl;
    outstr.resize(0);
    // cout << outstr.capacity() << endl;
}

void Update() {
    for (int i = 0; i < I; i++) {
        for (int j = 0; j < J; j++) {
            int numCells = getCells(i, j);
            space_1[i][j] =
                (numCells == 3 || (numCells == 2 && space[i][j])) ? 1 : 0;
        }
    }
    space.swap(space_1);
}

void Over() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "                                                  ";
    cout << "                                                  ";
    cout << " Game Over";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int getCells(int i, int j) {
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

string shitstr() {
    string result = "    ";
    for (int i = 0; i < J + 2; i++) {
        result.push_back('-');
    }
    result.push_back('\n');
    return result;
}
