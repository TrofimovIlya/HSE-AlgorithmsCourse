// �������� ����, 272(2)��
// ������ 6-7. ����������� ����������

#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
#include "trofimov_proekt6_main.h"
#include "trofimov_proekt6_auxiliaryMethods.h"
#include "trofimov_proekt6_sortings.h"

using namespace std;

int main() {
    setlocale(LC_ALL,"Russian");
    srand(time(0));

	cout << "1. ������������� �����;" << endl;
	cout << "2. ������� ����� �� ���������� �����;" << endl;
	cout << "3. �����.\n" << endl;

    int chosenItem;
	int N; // ������ ��������
	int NT; // ���������� ��������
	int min, max;
    int *array;
    bool flag = false;

	while (true) {
        if (flag) {
            cout << "\n1. ������������� �����;" << endl;
	        cout << "2. ������� ����� �� ���������� �����;" << endl;
	        cout << "3. �����.\n" << endl;
        } else {
            flag = true;
        }

		cout << "������� ����� ��������: ";
		cin >> chosenItem;
		if (!cin || chosenItem < 1 || chosenItem > 3) {
			cout << "�������� ������." << endl;
			cin.clear();
			while (cin.get() != '\n');
		}

		switch(chosenItem) {
		case 1: {
            	while(true) {
					cout << "������� ���������� ������ (��������): ";
					cin >> NT;
					if(!cin||NT<1) {
						cout << "�������� ������." << endl;
						cin.clear();
						while (cin.get() != '\n');
					}
					else break;
				}

				while(true) {
					cout << "������� ������ ��������: ";
					cin >> N;
					if(!cin||N<3) {
						cout << "�������� ������." << endl;
						cin.clear();
						while (cin.get() != '\n');
					} else { 
                        break;
                    }
				}

                array = new int[N];

            	while(true) {
					cout << "������� ����������� �������� ���������: ";
					cin >> min;
					if(!cin||min<0) {
						cout << "�������� ������." << endl;
						cin.clear();
						while (cin.get() != '\n');
					} else { 
                        break;
                    }
				}

                while(true) {
					cout << "������� ������������ �������� ���������: ";
					cin >> max;
					if(!cin||max>INT_MAX) {
						cout << "�������� ������." << endl;
						cin.clear();
						while (cin.get() != '\n');
					} else { 
                        break;
                    }
				}

				for(int i=0;i<NT;i++) {
                    generateArray(array, N, min, max);
                    sort(array, N);
                    cout << "\n" << endl;
				}

               
				break;
			}
		case 2: 
			{
				openFile();
				break;
			}
		case 3:
			{
				exit(1);
				break;
			}
		}

        delete [] array;
	}

    system("pause");
	return 0;
}


void sort(int *array, int n) {
    ofstream fOut;
	fOut.open("output_proekt6.txt", ios::app);

    int *testArray = new int[n];
    fOut << "�������� ������: " << endl;
    cout << "\n�������� ������: " << endl;
    printArray(array, n);
    saveArrayToFile(array, n, fOut);
    
    fOut << "\n������� ����������, ����������� � ��������: " << endl;
    cout << "\n������� ����������, ����������� � ��������: " << endl;
    cloneArray(array, testArray, n);
    middleQuickSort(testArray, 0, n - 1);
    printArray(testArray, n);
    saveArrayToFile(testArray, n, fOut);

    fOut << "\n������� ����������, ����������� � ������ �����: " << endl;
    cout << "\n������� ����������, ����������� � ������ �����: " << endl;
    cloneArray(array, testArray, n);
    leftQuickSort(testArray, 0, n - 1);
    printArray(testArray, n);
    saveArrayToFile(testArray, n, fOut);

    fOut << "\n������� ����������, ����������� � ���������: " << endl;
    cout << "\n������� ����������, ����������� � ���������: " << endl;
    cloneArray(array, testArray, n);
    randomQuickSort(testArray, 0, n - 1);
    printArray(testArray, n);
    saveArrayToFile(testArray, n, fOut);

    fOut << "\n���������� ��������: " << endl;
    cout << "\n���������� ��������: " << endl;
    cloneArray(array, testArray, n);
    mergeSort(testArray, 0, n - 1);
    printArray(testArray, n);
    saveArrayToFile(testArray, n, fOut);

    fOut << "\n������������� ����������: " << endl;
    cout << "\n������������� ����������: " << endl;
    cloneArray(array, testArray, n);
    heapSort(testArray, n);
    printArray(testArray, n);
    saveArrayToFile(testArray, n, fOut);
       
    fOut << "" << endl;
    fOut.close();

    delete [] testArray;
}

void openFile() {
	int NT, n;
	int* array;
	fstream file;
	
    try {
	file.open("input.txt",ios::in);
	file>>NT;
		for (int i = 0; i < NT; i++) {
			file >> n;
			array = new int[n]();

			for (int j = 0; j < n; j++) {
				file >> array[j];
			}

            sort(array, n);
            cout << "\n" << endl;

			delete [] array;
		}
	}
	
	catch(...) {
		cout << "������ ��� �������� �����." << endl;
	}
}

void saveArrayToFile(int *array, int n, ofstream& fOut) {
	for (int i = 0; i < n; i++) {
		fOut << array[i] << " ";
	}
    fOut << "" << endl;
}

void printArray(int *array, int n) {
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
}

void generateArray(int *array, int n, int min, int max) {
	for (int i = 0; i < n; i++) {
		array[i] = min + rand() % (max - min + 1);
	}
}