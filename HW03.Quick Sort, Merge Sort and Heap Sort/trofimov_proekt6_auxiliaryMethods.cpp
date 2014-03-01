// Трофимов Илья, 272(2)ПИ
// Проект 6-7. Рекурсивные сортировки

#include <iostream>
using namespace std;

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
