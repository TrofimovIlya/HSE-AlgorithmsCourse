/*
* @Author: Ilya Trofimov
* @Date:   2014-03-02 02:50:11
* @Last Modified by:   Ilya Trofimov
* @Last Modified time: 2014-03-02 20:50:00
*/

void bubbleSort(int array[], int length) {
    int temp = 0;

    for (int i = 0; i < length - 1; i++)
        for (int j = 0; j < length - 1 - i; j++)
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
}

void bubbleSort_booleanCondition(int array[], int length) {
    int temp = 0;
    bool wasSwap = true;

    for (int i = 0; wasSwap && i < length - 1; i++) {
        wasSwap = false;

        for (int j = 0; j < length - 1 - i; j++)
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1];

                wasSwap = true;
            }
    }
}

void bubbleSort_integerCondition(int array[], int length) {
    int temp = 0;
    int lastSwap = 0;

    for (int bound = length - 1; bound > 0; bound = lastSwap) {
        lastSwap = 0;

        for (int i = 0; i < bound; i++)
            if (array[i] > array[i + 1]) {
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;

                lastSwap = i;
            }
    }
}