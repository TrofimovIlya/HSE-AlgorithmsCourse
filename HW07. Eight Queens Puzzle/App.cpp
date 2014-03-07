/*
    Задача о восьми ферзях
    Выполнил: Трофимов Илья
    Группа: 272(2)
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int boardSize = 8;
bool board[boardSize][boardSize];
int numberOfSolutions = 0;

void saveBoard() {
    ofstream fi;
    fi.open ("output_queen.txt", ios::app);
    fi << "Solution number " << numberOfSolutions << ": " << endl;

    for (int a = 0; a < boardSize; ++a)
        for (int b = 0; b < boardSize; ++b)
            if (board[a][b]) {
                fi << a << b << endl;
                continue;
            }

    fi << endl;
    fi.close();
}

bool isValidPosition(int a, int b) {
    for (int i = 0; i < a; ++i) {
        if (board[i][b]) {
            return false;
        }
    }

    for (int i = 1; i <= a && b - i >= 0; ++i)
        if (board[a - i][b - i]) {
            return false;
        }

    for (int i = 1; i <= a && b + i < boardSize; i++)
        if (board[a - i][b + i]) {
            return false;
        }

    return true;
}


void placeQueen(int a) {
    if (a == boardSize) {
        saveBoard();
        ++numberOfSolutions;
    }

    for (int i = 0; i < boardSize; ++i)
        if (isValidPosition(a, i)) {
            board[a][i] = 1;
            placeQueen(a + 1);
            board[a][i] = 0;
        }
}

int main() {
    ofstream fi;
    fi.open ("output_queen.txt");
    fi << "";
    fi.close();

    placeQueen(0);
    return 0;
}