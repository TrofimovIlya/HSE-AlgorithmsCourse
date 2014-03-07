/*
* @Author: Ilya Trofimov
* @Date:   2014-03-02 02:27:18
* @Last Modified by:   Ilya Trofimov
* @Last Modified time: 2014-03-02 19:51:10
*/

void __heapify(int array[], int ind, int length) {
    int left = ind * 2 + 1;
    int right = ind * 2 + 2;
    int largest = 0;
    int temp = 0;

    if (left < length && array[left] > array[ind]) {
        largest = left;
    } else {
        largest = ind;
    }

    if (right < length && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != ind) {
        temp = array[largest];
        array[largest] = array[ind];
        array[ind] = temp;
        __heapify(array, largest, length);
    }
}

void __buildHeap(int array[], int length) {
    for (int i = length / 2; i >= 0; --i) {
        __heapify(array, i, length);
    }
}

void heapSort(int array[], int length) {
    __buildHeap(array, length);

    for (int i = length - 1; i >= 1; --i) {
        int temp = array[i];
        array[i] = array[0];
        array[0] = temp;
        __heapify(array, 0, i);
    }
}