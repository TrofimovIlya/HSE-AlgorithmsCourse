/*
* @Author: Ilya Trofimov
* @Date:   2014-03-02 18:49:21
* @Last Modified by:   Ilya Trofimov
* @Last Modified time: 2014-03-02 19:52:12
*/


#include <stdlib.h>

void __quickSort_middleSeparator(int array[], int low, int high) {
    int i = low;
    int j = high;
    int k = (i + j) / 2;
    int x = array[k];
    int temp = 0;

    do {
        while (array[i] < x) {
            i ++;
        }

        while (array[j] > x) {
            j --;
        }

        if (i <= j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i ++; j --;
        }
    } while (i <= j);

    if (low < j) {
        __quickSort_middleSeparator(array, low, j);
    }

    if (high > i) {
        __quickSort_middleSeparator(array, i, high);
    }

}

void __quickSort_secondSeparator(int array[], int low, int high) {
    int i = low;
    int j = high;
    int k;

    if (j - i > 0) {
        k = i + 1;
    } else {
        k = i;
    }

    int x = array[k];
    int temp = 0;

    do {
        while (array[i] < x) {
            i ++;
        }

        while (array[j] > x) {
            j --;
        }

        if (i <= j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++; j--;
        }
    } while (i <= j);

    if (low < j) {
        __quickSort_secondSeparator(array, low, j);
    }

    if (high > i) {
        __quickSort_secondSeparator(array, i, high);
    }
}

void __quickSort_randomSeparator(int array[], int low, int high) {
    int i = low;
    int j = high;
    int x = array[low + rand() % (high - low + 1)];
    int temp = 0;

    do {
        while (array[i] < x) {
            i ++;
        }

        while (array[j] > x) {
            j --;
        }

        if (i <= j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++; j--;
        }
    } while (i <= j);

    if (low < j) {
        __quickSort_randomSeparator(array, low, j);
    }

    if (high > i) {
        __quickSort_randomSeparator(array, i, high);
    }

}

void quickSort(int array[], int length) {
    __quickSort_middleSeparator(array, 0, length - 1);
}

void quickSort_middleSeparator(int array[], int length) {
    __quickSort_middleSeparator(array, 0, length - 1);
}

void quickSort_secondSeparator(int array[], int length) {
    __quickSort_secondSeparator(array, 0, length - 1);
}

void quickSort_randomSeparator(int array[], int length) {
    __quickSort_randomSeparator(array, 0, length - 1);
}