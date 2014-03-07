/*
    Автор: Трофимов Илья
    Группа: 272ПИ(2)
    Дата: 03.12.2013
    Номер проекта: 11
    Среда разработки: Microsoft Visual Studio 2012 Professional
*/

#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

// Prints an array
void print(long long *arr, long long n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }

    cout << endl;
}

// Calculates factorial
long long fact(long long n) {
    if (n == 0) {
        return 1;
    }

    return n * fact(n - 1);
}

// Counts accomodations
long long countAccommodation(long long n, long long k) {
    if (k == 1) {
        return n;
    }

    return (n - k + 1) * countAccommodation(n, k - 1);
}

// Counts combinations
long long countCombination(long long n, long long k) {
    long long **temp = new long long*[n + 1];

    for (int i = 0; i <= n; i++) {
        temp[i] = new long long[k + 1];
    }

    for (int i = 0; i <= n; i++) {
        temp[i][0] = 1;

        if (i <= k) {
            temp[i][j] = 0;
        }


    }

    for (int i = 0; i <= n; i++)
        for (int j = i + 1; j <= k; j++) {
            temp[i][j] = 0;
        }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= min(i, k); j++) {
            temp[i][j] = temp[i - 1][j - 1] + temp[i - 1][j];
        }

    long long result = temp[n][k];

    for (int i = 0; i <= n; i++) {
        delete [] temp[i];
    }

    delete [] temp;

    return result;
}

// Helper for iterationPermutation
bool isFinal(long long *permutation, long long n, long long k) {
    for (int i = n - 2; i >= n - k; --i)
        if (permutation[i] < permutation[i + 1]) {
            return false;
        }

    return true;
}

// Helper for iterationPermutation
void nextPermutation(long long *permutation, long long n) {
    int i, j;

    for (i = n - 2; permutation[i] > permutation[i + 1]; --i);

    for (j = n - 1; permutation[j] < permutation[i]; --j);

    swap(permutation[i], permutation[j]);

    for (int k = j; ; k++)
        if (k == n - 1 || permutation[j] > permutation[k + 1]) {
            swap(permutation[j], permutation[k]);
            break;
        }

    for (j = 0; j < n - i - j - 2; j++) {
        swap(permutation[i + j + 1], permutation[n - j - 1]);
    }
}

// Generates permuations by iterations
void generatesPermutationIteration(long long n) {
    long long *permutation = new long long[n];

    for (int i = 0; i < n; i++) {
        permutation[i] = i + 1;
    }


    print(permutation, n);

    if (n != 1) {
        do {
            nextPermutation(permutation, n);
            print(permutation, n);
        } while (!isFinal(permutation, n, n));
    }

    delete [] permutation;
}

// Generates permutations by recursion
void generatePermutationRecursive(long long n, long long k, long long *permutation) {
    if (k == n) {
        long long *arr = new long long[n];

        for (int i = 0; i < n; i++) {
            arr[permutation[i]] = i + 1;
        }

        print(arr, n);

        delete [] arr;

        return;
    }

    for (int i = 0; i < n; i++) {
        if (permutation[i] == -1) {
            permutation[i] = k;
            generatePermutationRecursive(n, k + 1, permutation);
            permutation[i] = -1;
        }
    }
}

// Generates accomodation
void generateAccommodation(long long n, long long k, vector<long long> permutation) {
    if (permutation.size() == k) {
        for (int i = 0; i < permutation.size(); i++) {
            cout << permutation[i] + 1 << ' ';
        }

        cout << endl;

        return;
    }

    for (int i = 0; i < n; i++)
        if (find(permutation.begin(), permutation.end(), i) == permutation.end()) {
            permutation.push_back(i);
            generateAccommodation(n, k, permutation);
            permutation.pop_back();
        }
}

// Generates combination
void generateCombination(long long n, long long k, long long l, vector<long long> permutation) {
    if (permutation.size() == k) {
        for (int i = 0; i < permutation.size(); i++) {
            cout << permutation[i] + 1 << ' ';
        }

        cout << endl;

        return;
    }

    for (int i = l; i < n; i++)
        if (find(permutation.begin(), permutation.end(), i) == permutation.end()) {
            permutation.push_back(i);
            generateCombination(n, k, i + 1, permutation);
            permutation.pop_back();
        }
}

// Generates pertition
void generatePartition(long long n, long long k, vector<long long> partition) {
    if (n == 0) {
        for (int i = 0; i < partition.size(); i++) {
            cout << partition[i] << ' ';
        }

        cout << endl;

        return;
    }

    for (int i = k; i > 0; --i)
        if (i <= n) {
            partition.push_back(i);
            generatePartition(n - i, i, partition);
            partition.pop_back();
        }
}

void main() {
    setlocale(LC_ALL, "Russian");
    int n, k, choice, subChoice;

    do {
        cout << "1 - Количество перестановок, размещений и сочетаний;"  << endl;
        cout << "2 - Генерация перестановок итерационым или рекурсивным способом;" << endl;
        cout << "3 - Генерация размещений;" << endl;
        cout << "4 - Генерация сочетаний;" << endl;
        cout << "5 - Генерация разбиений на слагаемые;" << endl;

        cout << "\n9 - Очистить консоль;" << endl;
        cout << "0 - Выход." << endl;

        cout << "\nВыберите задачу: ";
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            do {
                cout << "Введите количество элементов, n: ";
                cin >> n;
                cout << "Введите размер подмножества, k: ";
                cin >> k;
            } while (n < 1 || k < 1 || k >= n);

            cout << "Количество перестановок длины " << n << " равно: " << fact(n) << endl;
            cout << "Количество размещений из " << n << " по " << k << " равно: " << countAccommodation(n, k) << endl;
            cout << "Количество сочетаний из " << n << " по " << k << " равно: " << countCombination(n, k) << endl;
            cout << endl;
            system("pause");
            cout << endl;
        } else if (choice == 2) {
            do {
                cout << "1 - Генерация перестановок итерационым способом;" << endl;
                cout << "2 - Генерация перестановок рекурсивным способом;" << endl;
                cout << "\nВыберите задачу: ";
                cin >> subChoice;
            } while (subChoice > 2 || subChoice < 1);

            do {
                cout << "Введите количество элементов, n: ";
                cin >> n;
            } while (n < 1);

            if (subChoice == 1) {
                generatesPermutationIteration(n);
            } else if (subChoice == 2) {
                long long *permutation = new long long[n];

                for (int i = 0; i < n; i++) {
                    permutation[i] = -1;
                }

                generatePermutationRecursive(n, 0, permutation);
                delete [] permutation;
            }

            cout << endl;
            system("pause");
            cout << endl;
        } else if (choice == 3) {
            do {
                cout << "Введите количество элементов, n: ";
                cin >> n;
                cout << "Введите размер подмножества, k: ";
                cin >> k;
            } while (n < 1 || k < 1 || k >= n);

            vector<long long> accomodation;
            generateAccommodation(n, k, accomodation);
            vector<long long>().swap(accomodation);
            cout << endl;
            system("pause");
            cout << endl;
        } else if (choice == 4) {
            do {
                cout << "Введите количество элементов, n: ";
                cin >> n;
                cout << "Введите размер подмножества, k: ";
                cin >> k;
            } while (n < 1 || k < 1 || k >= n);

            vector<long long> combinations;
            generateCombination(n, k, 0, combinations);
            vector<long long>().swap(combinations);
            cout << endl;
            system("pause");
            cout << endl;
        } else if (choice == 5) {
            do {
                cout << "Введите количество элементов, n: ";
                cin >> n;
            } while (n < 1);

            vector<long long> partition;
            generatePartition(n, n, partition);
            vector<long long>().swap(partition);
            cout << endl;
            system("pause");
            cout << endl;
        } else if (choice == 9) {
            system("cls");
            // system("clr");
            // system("clear");
        }
    } while (choice != 0);
}