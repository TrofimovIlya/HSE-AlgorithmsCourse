//=============================================================================
// Problem: Bubble Sort and Iverson's versions of Bubble Sort Algorithm
// Student: Ilya Trofimov
// Group: 272
// Date: 09/26/2013
// OS: Mac OSX 10.8.5
// Compiler: i686-apple-darwin11-llvm-g++-4.2 (GCC) 4.2.1
// IDE: Eclipse Kepler. Eclipse C/C++ Development Tools v8.2.0
//=============================================================================

#include <iostream>
#include <ctime>
using namespace std;

void bubbleSort(int array[], int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (array[j + 1] < array[j]) {
                int temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
}

void iversionBubbleSort1(int array[], int N) {
    bool T = false;
    int i = 0;

    while ((i < N - 1) && !T) {
        T = true;

        for (int j = 0; j < N - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }

            T = false;
        }

        i = i + 1;
    }
}

void iversionBubbleSort2(int array[], int N) {
    int bound = N - 1;
    int t = 0;

    do {
        t = 0;

        for (int i = 0; i < bound; i++) {
            if (array[i] > array[i + 1]) {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                t = i;
            }
        }

        bound = t;
    } while (t != 0);
}

void printArray(int array[], int N) {
    for (int i = 0; i < N; i++) {
        cout << array[i] << " ";
    }
}

void copyArray(int inputArray[], int outputArray[], int N) {
    for (int i = 0; i < N; i++) {
        outputArray[i] = inputArray[i];
    }
}

void isArraySorted(int array[], int N) {
    for (int i = 0; i < N - 1; i++) {
        if (array[i] > array[i + 1]) {
            cout << "\n������ ������������." << endl;
            return;
        }
    }

    cout << "\n������ ����������." << endl;
}

void generateArray(int array[], int N) {
    int min, max;

    while (true) {
        cout << "������� ����������� ��������: ";
        cin >> min;

        if (!cin) {
            cout << "������. ������� ����������� �������� ��� ���: ";
            cin.clear();

            while (cin.get() != '\n');
        } else {
            break;
        }
    }

    while (true) {
        cout << "������� ������������� ��������: ";
        cin >> max;

        if (!cin || max <= min) {
            cout << "������. ������� ������������� �������� ��� ���: ";
            cin.clear();

            while (cin.get() != '\n');
        } else {
            break;
        }
    }

    srand(time(0));

    for (int i = 0; i < N; i++) {
        array[i] = min + rand() % (max - min + 1);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    bool isArrayCreated = false;
    int chosenItem;
    int arrayLength = 1;
    int *originalArray = new int[arrayLength];
    int *sortedArray = new int[arrayLength];

    cout << "1. ������������� ����� ������;" << endl;
    cout << "2. ���������� ���������;" << endl;
    cout << "3. ���������� ��������� � �������� ��������� 1;" << endl;
    cout << "4. ���������� ��������� � �������� ��������� 2;" << endl;
    cout << "5. �����." << endl;

    while (true) {
        cout << "\n������� ����� ������: ";
        cin >> chosenItem;

        if (!cin || chosenItem < 1 || chosenItem > 5) {
            cout << "������ �����.";
            cin.clear();

            while (cin.get() != '\n');
        }

        switch (chosenItem) {
        case 1: {
            isArrayCreated = true;

            while (true) {
                cout << "������� ������ �������: ";
                cin >> arrayLength;

                if (!cin) {
                    cout << "������ �����.";
                    cin.clear();

                    while (cin.get() != '\n');
                } else {
                    break;
                }
            }

            delete [] originalArray;
            delete [] sortedArray;

            originalArray = new int[arrayLength];
            sortedArray = new int[arrayLength];
            generateArray(originalArray, arrayLength);
            cout << "\n������:" << endl;
            printArray(originalArray, arrayLength);
            isArraySorted(originalArray, arrayLength);
            break;
        }

        case 2: {
            if (isArrayCreated) {
                copyArray(originalArray, sortedArray, arrayLength);
                cout << "\n������ �� ����������:" << endl;
                printArray(originalArray, arrayLength);
                isArraySorted(originalArray, arrayLength);
                bubbleSort(sortedArray, arrayLength);
                cout << "\n������ ����� ���������� ���������:" << endl;
                printArray(sortedArray, arrayLength);
                isArraySorted(sortedArray, arrayLength);
            } else {
                cout << "���������� ������ ������� ������." << endl;
            }

            break;
        }

        case 3: {
            if (isArrayCreated) {
                copyArray(originalArray, sortedArray, arrayLength);
                cout << "\n������ �� ����������:" << endl;
                printArray(originalArray, arrayLength);
                isArraySorted(originalArray, arrayLength);
                iversionBubbleSort1(sortedArray, arrayLength);
                cout << "\n������ ����� ���������� ��������� � 1 �������� ���������:" << endl;
                printArray(sortedArray, arrayLength);
                isArraySorted(sortedArray, arrayLength);
            } else {
                cout << "���������� ������ ������� ������." << endl;
            }

            break;
        }

        case 4: {
            if (isArrayCreated) {
                copyArray(originalArray, sortedArray, arrayLength);
                cout << "\n������ �� ����������:" << endl;
                printArray(originalArray, arrayLength);
                isArraySorted(originalArray, arrayLength);
                iversionBubbleSort2(sortedArray, arrayLength);
                cout << "\n������ ����� ���������� ��������� � 2 �������� ���������:" << endl;
                printArray(sortedArray, arrayLength);
                isArraySorted(sortedArray, arrayLength);
            } else {
                cout << "���������� ������ ������� ������." << endl;
            }

            break;
        }

        case 5: {
            delete [] originalArray;
            delete [] sortedArray;
            exit(1);
            break;
        }
        }

    }

    delete [] originalArray;
    delete [] sortedArray;
    return 0;
}