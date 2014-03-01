/*
    Author: Ilya Trofimov
    Date: Sat, 30 Nov 2013
*/

void radixSort(int array[], int length, int radix) {
    int max = array[0]; 

    for (int i = 0; i < length; i++) 
        if (array[i] > max)
            max = array[i];
    
    int* b = new int[length];
    
    long long exp = 1;

    while (max / exp > 0) {
        int* c = new int[radix];

        for (int i = 0; i < radix; ++i)
            c[i] = 0;
        for (int i = 0; i < length; i++)
            c[array[i] / exp % radix]++;
        for (int i = 1; i < radix; i++)
            c[i] += c[i - 1];
        for (int i = length - 1; i >= 0; --i)
            b[--c[array[i] / exp % radix]] = array[i];
        for (int i = 0; i < length; i++)
            array[i] = b[i];

        exp *= radix;

        delete [] c;
    }

    delete [] b;
}

void radixSort_8(int array[], int length) {
    radixSort(array, length, 8); 
}

void radixSort_10(int array[], int length) {
    radixSort(array, length, 10); 
}

void radixSort_16(int array[], int length) {
    radixSort(array, length, 16); 
}

void radixSort_256(int array[], int length) {
    radixSort(array, length, 256); 
}