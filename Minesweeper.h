#ifndef HEADER_3D3C3E96A5E1CC65
#define HEADER_3D3C3E96A5E1CC65

#include <vector>

struct coord {
    short int x;
    short int y;
};

struct board {
    int x;
    int y;
    std::vector<coord> mines;
};

struct endVars {
    bool win;
    bool end;
};

const char bomb = '*';
const char blank = '-';
const int rationBomb = 5;

int mod(int x, int y);
void t();

// Debug functions
void dispDebug(const board& bdCon, std::vector<std::vector<int>>& bdDisp);
void printMineCoords(const board& bdCon);

// Game start functions
void init(board& bd);
void bombGen(board& bd);
void checkR(int rx[], int ry[], const coord& s, const board& bdCon);
void boardGen(const board& bdCon, std::vector<std::vector<int>>& bd, std::vector<std::vector<char>>& bdDisp);

// Display functions
void disp(const board& bdCon, std::vector<std::vector<char>>& bdDisp);

// End game functions
bool gameover(bool win);
void dispBombs(std::vector<std::vector<char>>& bdDisp, std::vector<std::vector<int>>& bd, const board& bdCon);
void reset(std::vector<std::vector<int>>& bd, std::vector<std::vector<char>>& bdDisp, board& bdCon);

// Action functions
void guess(coord& g, const board& bdCon);
void zero(coord g, std::vector<std::vector<int>>& bd, std::vector<std::vector<char>>& bdDisp, const board& bdCon);
bool checkWin(std::vector<std::vector<char>>& bdDisp, const board& bdCon);
void action(coord g, std::vector<std::vector<int>>& bd, std::vector<std::vector<char>>& bdDisp, board& bdCon, endVars& e);

#endif // header guard

