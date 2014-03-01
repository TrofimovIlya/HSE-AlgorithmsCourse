/*
    Author: Ilya Trofimov
    Date: Sat, 14 Dec 2013
*/

#include <iostream>
#include <stdlib.h> 
#include "QuickSort.h"

using namespace std;

void printArray(int array[], int length) {
    for (int i = 0; i < length; ++i)
        cout << array[i] << " ";
    cout << endl;
}

void copyArray(int src[], int trgt[], int length) { 
	for (int i = 0; i < length; ++i) 
		trgt[i] = src[i];
}

void randomizeArray(int array[], int length, int min, int max) { 
	for (int i = 0; i < length; ++i)
		array[i] = min + (rand() % (max - min + 1));
}

void almostSort(int array[], int length, int swapNumber) { 
    quickSort(array, length);

    for (int i = 0; i < swapNumber;) {
        int first = rand() % length;
		int second = rand() % length;

		if (first != second & length > 1) {
			int temp = array[first]; 
			array[first] = array[second];
			array[second] = temp;
            ++i;
		}
    }
}

void descendingSort(int array[], int length) { 
    for (int i = length - 1; i > 0; --i)
        for (int j = 0; j < i; ++j)
            if (array[j] < array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
}

