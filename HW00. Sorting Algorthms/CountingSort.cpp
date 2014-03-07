/*
* @Author: Ilya Trofimov
* @Date:   2014-03-02 02:27:18
* @Last Modified by:   Ilya Trofimov
* @Last Modified time: 2014-03-02 19:52:10
*/


void countingSort(int array[], int length) {
    int max = array[0];

    for (int i = 1; i < length; ++i)
        if (array[i] > max) {
            max = array[i];
        }

    int *c = new int[max + 1];

    for (int i = 0; i < max + 1; ++i) {
        c[i] = 0;
    }

    for (int i = 0; i < length; ++i) {
        c[array[i]]++;
    }

    for (int i = 1; i < max + 1; ++i) {
        c[i] += c[i - 1];
    }

    int *res = new int[length];

    for (int i = length - 1; i >= 0; --i) {
        res[c[array[i]] - 1] = array[i];
        c[array[i]]--;
    }

    for (int i = 0; i < length; ++i) {
        array[i] = res[i];
    }

    delete[] c;
    delete[] res;
}