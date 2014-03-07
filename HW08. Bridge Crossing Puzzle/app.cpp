/*
    Задача о переправах
    Выполнил: Трофимов Илья
    Группа: 272(2)
*/

#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

int main() {
    ifstream fin ("input.txt");
    string rout;
    getline(fin, rout);
    fin.close();

    int *left = new int[rout.length() + 1];
    int *right = new int[rout.length() + 1];
    left[0] = 0;
    right[0] = 1;

    for (int i = 1; i <= rout.length(); i++) {
        if (rout[i - 1] == 'L') {
            left[i] = min(left[i - 1] + 1, right[i - 1] + 1);
            right[i] = min(left[i - 1] + 1, right[i - 1]);
        } else if (rout[i - 1] == 'R') {
            left[i] = min(left[i - 1], right[i - 1] + 1);
            right[i] = min(left[i - 1] + 1, right[i - 1] + 1);
        } else if (rout[i - 1] == 'B') {
            left[i] = min(left[i - 1] + 1, right[i - 1] + 2);
            right[i] = min(left[i - 1] + 2, right[i - 1] + 1);
        }
    }

    ofstream fout ("output.txt");
    cout << rout << ": " << min(left[rout.length()] + 1, right[rout.length()]) << endl;
    fout << min(left[rout.length()] + 1, right[rout.length()]) << endl;
    fout.close();

    delete [] left;
    delete [] right;

    system("pause");
    return 0;
}