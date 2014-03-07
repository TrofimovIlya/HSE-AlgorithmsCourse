// Трофимов Илья, 272(2)ПИ
// Проект 6-7. Рекурсивные сортировки

#include <iostream>

void middleQuickSort(int *a, int first, int last) {
    int determinate = (first + last) / 2;
    int x = a[determinate];

    int i = first;
    int j = last;

    do {
        while (a[i] < x) {
            i++;
        }

        while (a[j] > x) {
            j--;
        }

        if (i <= j) {
            if (i < j) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }

            i++;
            j--;
        }
    } while (i <= j);

    if (i < last) {
        middleQuickSort(a, i, last);
    }

    if (first < j) {
        middleQuickSort(a, first, j);
    }
}

void leftQuickSort(int *a, int first, int last) {
    int determinate = first + 1;
    int x = a[determinate];

    int i = first;
    int j = last;

    do {
        while (a[i] < x) {
            i++;
        }

        while (a[j] > x) {
            j--;
        }

        if (i <= j) {
            if (i < j) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }

            i++;
            j--;
        }
    } while (i <= j);

    if (i < last) {
        leftQuickSort(a, i, last);
    }

    if (first < j) {
        leftQuickSort(a, first, j);
    }
}

void randomQuickSort(int *a, int first, int last) {
    int determinate = first + 1 + rand() % (last - first);
    int x = a[determinate];

    int i = first;
    int j = last;

    do {
        while (a[i] < x) {
            i++;
        }

        while (a[j] > x) {
            j--;
        }

        if (i <= j) {
            if (i < j) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }

            i++;
            j--;
        }
    } while (i <= j);

    if (i < last) {
        randomQuickSort(a, i, last);
    }

    if (first < j) {
        randomQuickSort(a, first, j);
    }
}

void merge(int *a, int left, int middle, int right) {
    int *b = new int[right + 1 - left];

    int h, i, j, k;
    h = left;
    i = 0;
    j = middle + 1;

    while ((h <= middle) && (j <= right)) {
        if (a[h] <= a[j]) {
            b[i] = a[h];
            h++;
        } else {
            b[i] = a[j];
            j++;
        }

        i++;
    }

    if (h > middle) {
        for (k = j; k <= right; k++) {
            b[i] = a[k];
            i++;
        }
    } else {
        for (k = h; k <= middle; k++) {
            b[i] = a[k];
            i++;
        }
    }

    for (k = 0; k <= right - left; k++) {
        a[k + left] = b[k];
    }

    delete[] b;
}

void mergeSort(int *a, int left, int right) {
    int middle;

    if (left < right) {
        middle = (left + right) / 2;
        mergeSort(a, left, middle);
        mergeSort(a, middle + 1, right);
        merge(a, left, middle, right);
    }
}

void downHeap(int *a, int k, int n) {
    int newElement;
    int value;
    newElement = a[k];

    while (k <= n / 2) {
        value = 2 * k;

        if (value < n && a[value] < a[value + 1]) {
            value++;
        }

        if (newElement >= a[value]) {
            break;
        }

        a[k] = a[value];
        k = value;
    }

    a[k] = newElement;
}

void heapSort(int *a, int n) {
    int i;
    int temp;

    for (i = n / 2 - 1; i >= 0; --i) {
        downHeap(a, i, n - 1);
    }

    for (i = n - 1; i > 0; --i) {
        temp = a[i];
        a[i] = a[0];
        a[0] = temp;
        downHeap(a, 0, i - 1);
    }
}