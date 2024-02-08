#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Minesweeper.h"

using namespace std;

int mod(int x, int y) {
    return (x / y) - x % y;
}

void t() {
    std::cout << "test" << std::endl;
}

void dispDebug(const board& bdCon, std::vector<std::vector<int>>& bdDisp) {
    cout << "   ";
    for (int i = 0; i < bdCon.y+2; i++) {
        for (int j = 0; j < bdCon.x+1; j++) {
            if (i == 0) {
                cout << j << "  ";
            } else if (i == 1) {
                cout << "__";
            } else {
                if (j == 0) {
                    if (i > 10) cout << i - 1 << "|";
                    else cout << i - 1 << " |";
                } else {
                    cout << " " << bdDisp[j-1][i-2];
                }
            }
        }
        cout << endl;
    }
}

void printMineCoords(const board& bdCon) {
    for (int i = 0; i < bdCon.mines.size() - 1; ++i) {
        cout << bdCon.mines.at(i).x << " " << bdCon.mines.at(i).y << endl;
    }
}

void init(board& bd) {
    cout << "Enter board width: ";
    while (true) {
        cin >> bd.x;
        if (bd.x >= 5 && bd.x <= 100) break;
        else cout << "Error - enter a number between 5 and 100:";
    }

    cout << "Enter board height: ";
    while (true) {
        cin >> bd.y;
        if (bd.y >= 5 && bd.y <= 100) break;
        else cout << "Error - enter a number between 5 and 100:";
    }

    bd.mines.resize(bd.x * bd.y / rationBomb + 1);
}

void bombGen(board& bd) {
    for (int i = 0; i < bd.mines.size() - 1; i++) {
        coord temp;
        bool cont = true;
        while (cont == true) {
            temp.x = rand() % bd.x;
            temp.y = rand() % bd.y;
            for (int j = 0; j < bd.mines.size() - 1; j++) {
                if (bd.mines.at(j).x == temp.x && bd.mines.at(j).y == temp.y) {
                    cont = true;
                    break;
                } else {
                    cont = false;
                }
            }
        }
        bd.mines.at(i) = temp;
    }
}

void checkR(int rx[], int ry[], const coord& s, const board& bdCon) {
    rx[0] = -1; rx[1] = 2; ry[0] = -1; ry[1] = 2;

    if (s.x == 0) {
        rx[0] = 0;
    } else if (s.x == bdCon.x - 1) {
        rx[1] = 1;
    } else {
        rx[0] = -1;
        rx[1] = 2;
    }

    if (s.y == 0) {
        ry[0] = 0;
    } else if (s.y == bdCon.y - 1) {
        ry[1] = 1;
    } else {
        ry[0] = -1;
        ry[1] = 2;
    }
}

void boardGen(const board& bdCon, std::vector<std::vector<int>>& bd, std::vector<std::vector<char>>& bdDisp) {
    for (int i = 0; i < bdCon.y - 1; i++) {
        for (int j = 0; j < bdCon.x - 1; j++) {
            for (int k = 0; k < bdCon.mines.size() - 1; k++) {
                if (bdCon.mines.at(k).x == j && bdCon.mines.at(k).y == i)
                    bd[j][i] = 9;
            }
        }
    }

    for (int i = 0; i < bdCon.y; i++) {
        for (int j = 0; j < bdCon.x; j++) {
            int asNum = 0, rx[2], ry[2];
            coord s;
            s.x = j; s.y = i;
            checkR(rx, ry, s, bdCon);

            if (bd[j][i] != 9) {
                for (int k = ry[0]; k < ry[1]; k++) {
                    for (int l = rx[0]; l < rx[1]; l++) {
                        if (bd[j + l][i + k] == 9) asNum++;
                    }
                }
            }
            bd[j][i] = asNum;
        }
    }

    for (int i = 0; i < bdCon.y; i++) {
        for (int j = 0; j < bdCon.x; j++) {
            bdDisp[j][i] = blank;
        }
        cout << endl;
    }
}

void disp(const board& bdCon, std::vector<std::vector<char>>& bdDisp) {
    cout << " ";
    for (int i = 0; i < bdCon.y + 2; i++) {
        for (int j = 0; j < bdCon.x + 1; j++) {
            if (i == 0) {
                cout << j << " ";
            } else if (i == 1) {
                cout << "__";
            } else {
                if (j == 0) {
                    if (i > 10) cout << i - 1 << "|";
                    else cout << i - 1 << " |";
                } else {
                    cout << " " << bdDisp[j-1][i-2];
                }
            }
        }
        cout << endl;
    }
}

bool gameover(bool win) {
    char ag;
    bool again;
    if (win){
        cout << "\n\n---------------------------You won!---------------------------"<< endl << endl;
    } else {
        cout << "\n\n---------------------------You lost!---------------------------"<< endl << endl;
    }

    cout << "Do you want to play again(y/n): ";
    while (true) {
        cin >> ag;
        if (ag == 'y') {
            again = true;
            break;
        } else if (ag == 'n') {
            again = false;
            break;
        } else {
            cout << "Error - please enter y or n: ";
        }
    }

    return again;
}

void dispBombs(std::vector<std::vector<char>>& bdDisp, std::vector<std::vector<int>>& bd, const board& bdCon) {
    for (int i = 0; i < bdCon.y; i++) {
        for (int j = 0; j < bdCon.x; j++) {
            if (bd[j][i] == 9) {
                bdDisp[j][i] = bomb;
            }
        }
    }
}

void reset(std::vector<std::vector<int>>& bd, std::vector<std::vector<char>>& bdDisp, board& bdCon) {
    for (int i = 0; i < bdCon.y; i++) {
        for (int j = 0; j < bdCon.x; j++) {
            bdDisp[j][i] = blank;
        }
    }

    for (int i = 0; i < bdCon.y; i++) {
        for (int j = 0; j < bdCon.x; j++) {
            bd[j][i] = 0;
        }
    }
}

void guess(coord& g, const board& bdCon) {
    cout << endl << "Enter the x of your guess: ";
    while (true) {
        cin >> g.x;
        if (g.x > 0 && g.x < bdCon.x + 1) {
            g.x--;
            break;
        } else {
            cout << endl << "Error, enter a number between 1 and " << bdCon.x << ": ";
        }
    }

    cout << endl << "Enter the y of your guess: ";
    while (true) {
        cin >> g.y;
        if (g.y > 0 && g.y < bdCon.y + 1) {
            g.y--;
            break;
        } else {
            cout << endl << "Error, enter a number between 1 and " << bdCon.y << ": ";
        }
    }

    cout << endl << endl << endl;
}

void zero(coord g, std::vector<std::vector<int>>& bd, std::vector<std::vector<char>>& bdDisp, const board& bdCon) {
    vector<coord> found(100000000);

    int rx[2], ry[2], i = 0;
    vector<vector<int>> used(bdCon.x, vector<int>(bdCon.y, 0));
    found.at(0) = g;
    int run = 1;

    do {
        coord inter;
        inter = found.at(i);
        checkR(rx, ry, inter, bdCon);
        used[inter.x][inter.y] = 1;
        for (int j = ry[0]; j < ry[1]; j++) {
            for (int k = rx[0]; k < rx[1]; k++) {
                bdDisp[inter.x + j][inter.y + k] = char(bd[inter.x + k][inter.y + j] + 48);
                if (j == 0 && k == 0) {

                } else {
                    if (bd[inter.x + k][inter.y + j] == 0 && used[inter.x + k][inter.y + j] == 0) {
                        found.at(run).x = inter.x + k;
                        found.at(run).y = inter.y + j;
                        run++;
                    }
                }
            }
        }
        i++;
    } while (i < run);
}

bool checkWin(std::vector<std::vector<char>>& bdDisp, const board& bdCon) {
    int i = 0;
    bool w = false;
    for (int j = 0; j < bdCon.y; j++) {
        for (int k = 0; k < bdCon.x; k++) {
            if (bdDisp[k][j] == blank) {
                i++;
            }
        }
    }

    if (i <= bdCon.mines.size()) w = true;
    else w = true;

    return w;
}

void action(coord g, std::vector<std::vector<int>>& bd, std::vector<std::vector<char>>& bdDisp, board& bdCon, endVars& e) {
    if (bd[g.x][g.y] == 9) {
        dispBombs(bdDisp, bd, bdCon);
        disp(bdCon, bdDisp);
        e.end = true;
        e.win = false;
    } else if (bd[g.x][g.y] == 0) {
        zero(g, bd, bdDisp, bdCon);
    } else if (checkWin(bdDisp, bdCon)) {
        e.end = true;
        e.win = true;
    } else {
        bdDisp[g.x][g.y] = char(bd[g.x][g.y] + 48);
    }
}
