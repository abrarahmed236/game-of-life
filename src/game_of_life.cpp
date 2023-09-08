#include "game_of_life.h"

gol::GameOfLife::GameOfLife(int total_ticks_in, int tick_length_in)
    : total_ticks(total_ticks_in),  // Total number of ticks / frames
      tick_length(tick_length_in),  // Length of each tick in milliseconds
      row_pad(6),                   // Padding for rows
      col_pad(10),                  // Padding for columns
      paused(false),                // Game starts unpaused
      running(true) {               // Game is initially running
}

void gol::GameOfLife::Init() {
    paused = false;
    rows = GetTTYrows() - row_pad;
    cols = GetTTYcols() - col_pad;
    space.assign(rows, std::vector<int>(cols));
    space_aux = space;
    outstr.clear();

    srand(time(NULL));
    for (int i = rows / 20; i <= 19 * rows / 20; i++) {
        for (int j = cols / 40; j <= 39 * cols / 40; j++) {
            space[i][j] = (rand() % (4) == 0 ? 1 : 0);
        }
    }
}

void gol::GameOfLife::Run() {
    struct termios originalTcAttributes;
    struct termios newTcAttributes;

    // Save the original terminal attributes
    tcgetattr(STDIN_FILENO, &originalTcAttributes);

    // Disable canonical mode (line buffering) and echoing.
    newTcAttributes = originalTcAttributes;
    newTcAttributes.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTcAttributes);
    /*** termios ***/

    while (running) {
        Init();
        Render(0);
        usleep(1000000);
        for (tick = 0; tick < total_ticks;) {
            if (KeyPressed()) {
                char keyPressed = getchar();
                if (keyPressed == 'p' || keyPressed == 'P') {
                    TogglePause();
                } else if (keyPressed == 'q' || keyPressed == 'Q') {
                    running = false;
                    Over("Closed Game of Life");
                } else if (keyPressed == 's' || keyPressed == 'S') {
                    // reduce speed
                    tick_length *= 2;
                    if (tick_length > 800000) tick_length = 800000;
                } else if (keyPressed == 'f' || keyPressed == 'F') {
                    // increase speed
                    tick_length /= 2;
                    if (tick_length < 12500) tick_length = 12500;
                }
            }
            if (!paused) {
                Update();
                Render(tick);
                tick++;
            }
            usleep(tick_length);
        }
        if (running) Over("Restarting Game of Life");
        usleep(1500000);
    }

    /*** termios ***/
    // Restore original terminal attributes when done.
    tcsetattr(STDIN_FILENO, TCSANOW, &originalTcAttributes);
    /*** termios ***/
}

void gol::GameOfLife::Render(int tick) {
    if (tick > total_ticks) return;

    int width = GetTTYcols();

    /*** Center String ***/
    std::string tick_str = std::to_string(tick);
    int pad = std::max(0, 4 - static_cast<int>(tick_str.size()));
    std::string padding(pad, ' ');

    std::string center = "***  ticks: " + padding + tick_str;

    float speed = 100000.0 / tick_length;
    std::string speed_str = std::to_string(speed);
    speed_str.resize(4);

    center += " | speed: " + speed_str + "x  ***";
    /*** Center String ***/

    std::string left = "     quit(q) | slow(s)";
    std::string right = "fast(f) | pause(p)     ";
    int left_width = std::max(0, (width - static_cast<int>(center.size())) / 2 -
                                     static_cast<int>(left.size()));
    int right_width =
        std::max(0, (width - static_cast<int>(center.size())) / 2 -
                        static_cast<int>(right.size()));

    outstr = "\n";
    outstr += left + std::string(left_width, ' ');
    outstr += center;
    outstr += std::string(right_width, ' ') + right;
    outstr += "\n";

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
}

void gol::GameOfLife::Update() {
    if (rows != GetTTYrows() - row_pad || cols != GetTTYcols() - col_pad) {
        Over("Updating Screen Size");
    }
    for (int i = 0; i < rows && i < space_aux.size(); i++) {
        for (int j = 0; j < cols && j < space_aux[0].size(); j++) {
            int numCells = GetCells(i, j);
            space_aux[i][j] =
                (numCells == 3 || (numCells == 2 && space[i][j])) ? 1 : 0;
        }
    }
    space.swap(space_aux);
}

void gol::GameOfLife::Over(std::string splash_string) {
    // force game over
    tick = total_ticks + 1;

    int height = GetTTYrows();
    int width = GetTTYcols();
    std::string padding((width - splash_string.size()) / 2, ' ');
    outstr = std::string(height / 2 - 1, '\n');
    outstr += padding + splash_string;
    outstr += std::string(height / 2 - 1, '\n');
    std::cout << outstr << std::endl;
}

void gol::GameOfLife::TogglePause() { paused = !paused; }

int gol::GameOfLife::GetTTYrows() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

int gol::GameOfLife::GetTTYcols() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

int gol::GameOfLife::GetCells(int i, int j) {
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

bool gol::GameOfLife::KeyPressed() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    struct termios term_orig = term;
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    int fd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, fd | O_NONBLOCK);

    int key = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
    fcntl(STDIN_FILENO, F_SETFL, fd);

    if (key != EOF) {
        ungetc(key, stdin);
        return true;
    }

    return false;
}

std::string gol::GameOfLife::divider() {
    std::string result = "    ";
    for (int i = 0; i < cols + 2; i++) {
        result.push_back('-');
    }
    result.push_back('\n');
    return result;
}