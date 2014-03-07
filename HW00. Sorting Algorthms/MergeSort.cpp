/*
* @Author: Ilya Trofimov
* @Date:   2014-03-02 19:12:01
* @Last Modified by:   Ilya Trofimov
* @Last Modified time: 2014-03-02 19:51:14
*/


void __merge(int array[], int start, int middle, int end) {
    int *temp = new int[end + 1];

    for (int i = start; i <= end; i++) {
        temp[i] = array[i];
    }

    int position1 = start;
    int position2 = middle + 1;

    for (int i = start; i <= end; i++)
        if (position1 > middle || ((temp[position1] > temp[position2]) && position2 <= end)) {
            array[i] = temp[position2];
            position2++;
        } else {
            array[i] = temp[position1];
            position1++;
        }

    delete [] temp;
}

void __mergeSort(int array[], int start, int end) {
    if (start < end) {
        int middle = (start + end) / 2;
        __mergeSort(array, start, middle);
        __mergeSort(array, middle + 1, end);
        __merge(array, start, middle, end);
    }
}

void mergeSort(int array[], int length) {
    __mergeSort(array, 0, length - 1);
}