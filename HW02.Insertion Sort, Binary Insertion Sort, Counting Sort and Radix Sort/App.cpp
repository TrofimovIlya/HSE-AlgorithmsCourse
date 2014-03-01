//=============================================================================
// Problem: Insertion sort, Binary Insertion sort, Counting sort and Radix sort
// Student: Ilya Trofimov
// Group: 272
// Date: 10/02/2013
// IDE: Microsoft Visual Studio 2012
//=============================================================================

#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>

using namespace std;

void insertionSort(int *array, int n);
void binaryInsertionSort(int *array, int n);
void countingSort(int *array, int n);
void radixSort(int *array, int n, int base);
void sort(int *array, int n);
int getMin(int *array, int n);
int getMax(int *array, int n); 
bool isArraySorted(int *array, int n);
void printArray(int *array, int n);
void generateArray(int *array, int n, int min, int max);
void cloneArray(int *inputArray, int *outputArray, int n);
void saveArrayToFile(int *array, int n, ofstream& fOut);
void openFile();

int main() {
    setlocale(LC_ALL,"Russian");
    srand(time(0));

	cout << "1. Сгенерировать тесты;" << endl;
	cout << "2. Считать тесты из текстового файла;" << endl;
	cout << "3. Выйти.\n" << endl;

    int chosenItem;
	int N; // размер массивов
	int NT; // количество массивов
	int min, max;
    int *array;
    bool flag = false;

	while (true) {
        if (flag) {
            cout << "\n1. Сгенерировать тесты;" << endl;
	        cout << "2. Считать тесты из текстового файла;" << endl;
	        cout << "3. Выйти.\n" << endl;
        } else {
            flag = true;
        }

		cout << "Введите номер действия: ";
		cin >> chosenItem;
		if (!cin || chosenItem < 1 || chosenItem > 3) {
			cout << "Неверные данные." << endl;
			cin.clear();
			while (cin.get() != '\n');
		}

		switch(chosenItem) {
		case 1: {
            	while(true) {
					cout << "Введите количество тестов (массивов): ";
					cin >> NT;
					if(!cin||NT<1) {
						cout << "Неверные данные." << endl;
						cin.clear();
						while (cin.get() != '\n');
					}
					else break;
				}

				while(true) {
					cout << "Введите размер массивов: ";
					cin >> N;
					if(!cin||N<2) {
						cout << "Неверные данные." << endl;
						cin.clear();
						while (cin.get() != '\n');
					} else { 
                        break;
                    }
				}

                array = new int[N];

            	while(true) {
					cout << "Введите минимальное значение элементов: ";
					cin >> min;
					if(!cin||min<0) {
						cout << "Неверные данные." << endl;
						cin.clear();
						while (cin.get() != '\n');
					} else { 
                        break;
                    }
				}

                while(true) {
					cout << "Введите максимальное значение элементов: ";
					cin >> max;
					if(!cin||max>INT_MAX) {
						cout << "Неверные данные." << endl;
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

                delete [] array;
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

	}

    system("pause");
	return 0;
}


void insertionSort(int *array, int n) {
	for (int i = 1; i < n; i++) {
		int j = i;
		while (j > 0 && array[j] < array[j - 1]) {
			int temp = array[j];
			array[j] = array[j - 1];
			array[j - 1] = temp;
			j = j - 1;
		}
	}
}

void binaryInsertionSort(int *array, int n) {
	for (int i = 1; i < n; i++) {
		int leftBound = 0;
		int rightBound = i;
		int middle = (leftBound + rightBound) / 2;

		while (leftBound != middle) {
			if (array[middle] > array[i]) {
				rightBound = middle - 1;
			} else {
				leftBound = middle;
			}

			middle = (leftBound + rightBound) / 2;
		}

		if (array[leftBound] < array[i]) {
			if (array[i] > array[rightBound]) {
				leftBound = rightBound + 1;
			} else {
			    leftBound = rightBound;
			}
		}

		int temp = array[i];

		for (int j = i; j > leftBound; j--) {
			array[j] = array[j - 1];
		}

		array[leftBound] = temp;
	}
}

void countingSort(int *array, int n) {
	int min = getMin(array, n);
	int max = getMax(array, n);
    int tempLegth = max - min + 1;
    int *temp = new int[tempLegth];
	
    memset(temp, 0, tempLegth * sizeof(int)); // Заполняем нулями массив temp
 
	for (int i = 0; i < n; i++) {
        temp[array[i] - min]++;
    }

    int j = 0;

	for(int i = min; i <= max; i++) {
	    while(temp[i - min]) {
		array[j++] = i;
		temp[i - min]--;
	    }
	}
 
	delete [] temp;
}

void radixSort(int *array, int n, int base) {
    int exponent = 1; 
    int max = getMax(array, n);
    int *temp = new int[n]();

    while (max / exponent > 0) {
        int *cnt = new int[base]();
        cloneArray(array, temp, n);

        for (int i = 0; i < n; i++) {
            cnt[(temp[i] / exponent) % base]++;
        }    
        
        int sum = 0, j;
        for (int i = 0; i < base; i++) {
            j = cnt[i];
            cnt[i] = sum;
            sum += j;
        }
        
        for (int i = 0; i < n; i++) {
            int tempIndex = (temp[i] / exponent) % base;
            array[cnt[tempIndex]] = temp[i];
            cnt[tempIndex]++;
        }
        
        exponent *= base;
        delete [] cnt;
    }

    delete [] temp;
}

void sort(int *array, int n) {
    ofstream fOut;
	fOut.open("output.txt", ios::app);

    int *testArray = new int[n];
    fOut << "Исходный массив: " << endl;
    cout << "\nИсходный массив: " << endl;
    printArray(array, n);
    saveArrayToFile(array, n, fOut);
    
    fOut << "\nСортировка вставками: " << endl;
    cout << "\nСортировка вставками: " << endl;
    cloneArray(array,testArray,n);
    insertionSort(testArray, n);
    printArray(testArray, n);
    saveArrayToFile(testArray, n, fOut);
    
    cout << "\nСортировка бинарными вставками: " << endl;
    fOut << "\nСортировка бинарными вставками: " << endl;
    cloneArray(array,testArray,n);
    binaryInsertionSort(testArray, n);
    printArray(testArray, n);
    saveArrayToFile(testArray, n, fOut);

    cout << "\nСортировка подсчетом: " << endl;
    fOut << "\nСортировка подсчетом: " << endl;
    cloneArray(array,testArray,n);
    countingSort(testArray, n);
    printArray(testArray, n);
    saveArrayToFile(testArray, n, fOut);

    cout << "\nЦифровая сортировка по основанию 10: " << endl;
    fOut << "\nЦифровая сортировка по основанию 10: " << endl;
    cloneArray(array,testArray,n);
    radixSort(testArray, n, 10);
    printArray(testArray, n);
    saveArrayToFile(testArray, n, fOut);
    
    cout << "\nЦифровая сортировка по основанию 256: " << endl;
    fOut << "\nЦифровая сортировка по основанию 256: " << endl;
    cloneArray(array,testArray,n);
    radixSort(testArray, n, 256);
    printArray(testArray, n);
    saveArrayToFile(testArray, n, fOut);

    fOut << "" << endl;
    fOut.close();

    delete [] testArray;
}

void saveArrayToFile(int *array, int n, ofstream& fOut) {
	for (int i=0; i < n; i++) {
		fOut << array[i] << " ";
	}
    fOut << "" << endl;
}

int getMin(int *array, int n) {
    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (array[i] < min) {
            min = array[i];
        }
    }
    return min;
}

int getMax(int *array, int n) {
    int max = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

void printArray(int *array, int n) {
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
}

bool isArraySorted(int *array, int n) {
	for (int i = 0; i < n - 1; i++) {
		if (array[i] > array[i + 1]) {
			return false;
		}
	}
	return true;
}

void cloneArray(int *inputArray, int *outputArray, int n) {
	for (int i = 0; i < n; i++) {
		outputArray[i] = inputArray[i];
	}
}

void generateArray(int *array, int n, int min, int max) {
	for (int i = 0; i < n; i++) {
		array[i] = min + rand() % (max - min + 1);
	}
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
		cout << "Ошибка при открытии файла." << endl;
	}
}


