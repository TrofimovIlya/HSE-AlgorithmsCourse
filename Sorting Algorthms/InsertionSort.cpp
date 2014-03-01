/*
    Author: Ilya Trofimov
    Date: Sat, 30 Nov 2013
*/

void insertionSort(int array[], int length) {
    for (int i = 1; i < length; ++i) {
        int j = i - 1;

        for (; j >= 0 && array[j] > array[i]; --j)
            array[j + 1] = array[j];

        array[j + 1] = array[i];
    }
}

void binaryInsertionSort(int array[], int length)
{    
	int i, j, left, right, mid;   
	int P;   
	i = 1;
    do {
        left = 0;
        right = i - 1;
        mid = (left + right)/2;
        while (left != mid) {
            if (array[mid] > array[i]) {
				right = mid-1;
			}
			else {
				left = mid;
			}
            mid = (left + right)/2;
        }
        if (array[left] < array[i]) {
            if (array[i] > array[right]) {
				left = right + 1;
			}
			else {
				left = right;
			}
		}
        j = i;
        P = array[i];
        while (j > left) {
            array[j] = array[j-1];
            j -= 1;
        }
        array[left] = P;
        i += 1;
    } while (i < length);	
} 
