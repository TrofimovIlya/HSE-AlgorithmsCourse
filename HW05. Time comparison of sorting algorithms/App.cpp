/*
    Author: Ilya Trofimov
    Date: Sat, 14 Dec 2013
*/

#include <iostream>
#include <ctime> 
#include <fstream>
#include <string>
#include <Windows.h>
#include "Sortings.h"
#include "AuxiliaryMethods.h"

using namespace std;

ofstream out("results.txt");

long long timeCount(void (*sorting)(int[], int), int array[], int length) {
    LARGE_INTEGER Fr, StT, FT, TT;
    QueryPerformanceCounter(&StT);
    QueryPerformanceFrequency(&Fr);

    sorting(array, length); 

    QueryPerformanceCounter(&FT);
    TT.QuadPart = FT.QuadPart - StT.QuadPart;
    TT.QuadPart = TT.QuadPart * 1000000000 / Fr.QuadPart;

    return TT.QuadPart;
}

void startTest(void (*sorting)(int[], int), int minValue, int maxValue, int arrayType = 0) {
    const int testCount = 20;

    out << "length" << "\t" << "average" << "\t" << "min" << "\t" << "max" << endl; 
    
    for (int length = 1000; length <= 8000; length += 1000) {
        cout << "Размер массива: " << "\t\t" << length << endl; 
    
        long long minTime = INT_MAX;
        long long maxTime = INT_MIN;
        long long totalTime = 0;

        int* originalArray = new int[length];
        int* testArray = new int[length];
        randomizeArray(originalArray, length, minValue, maxValue);

        if (arrayType == 3)
            quickSort(originalArray, length);
        else if (arrayType == 4)
            almostSort(originalArray, length, 5);
        else if (arrayType == 5)
            descendingSort(originalArray, length);

        for (int i = 0; i < testCount; ++i) { 
            copyArray(originalArray, testArray, length);

            long long lastTime = timeCount(sorting, testArray, length);

            if (lastTime > maxTime)
                maxTime = lastTime;
            
            if (lastTime < minTime) 
                minTime = lastTime;

            totalTime += lastTime; 
        }

        out << length << "\t" << (totalTime / testCount) << "\t" << minTime << "\t" << maxTime << endl; 
        cout << "Среднее время сортировки: " << "\t" << (totalTime / testCount) << " нс" << endl; 
        cout << "Минимальное время сортировки: " << "\t" << minTime << " нс" << endl;
        cout << "Максимальное время сортировки: " << "\t" << maxTime << " нс" << endl << endl; 
        

        delete [] originalArray;
        delete [] testArray;	
    }

    out << endl << endl;
    cout << endl << endl;
}

void test(string sortingName, void (*sorting)(int[], int), bool allowNegative = true, bool allowMax = true) {
    out << "/========================= " << sortingName << " =========================/" << endl << endl;
    cout << "/===== " << sortingName << " =====/" << endl << endl;

    if (allowNegative) {
        out << "Массив не отсортирован и все элементы массива - случайные значения от -2 до 2" << endl << endl;
        cout << "Массив не отсортирован, [-2; 2]" << endl << endl;
        startTest(sorting, -2, 2);
    } else {
        out << "Массив не отсортирован и все элементы массива - случайные значения от 0 до 4" << endl << endl;
        cout << "Массив не отсортирован, [0; 4]" << endl << endl;
        startTest(sorting, 0, 4);
    }
    
    if (allowMax) {
        out << "Массив не отсортирован и все элементы массива - случайные значения от 0 до INT_MAX" << endl << endl;
        cout << "Массив не отсортирован, [0; INT_MAX]" << endl << endl;
        startTest(sorting, 0, INT_MAX);
    }        

    out << "Массив отсортирован и все элементы массива - случайные значения от 0 до 100" << endl << endl;
    cout << "Массив отсортирован, [0; 100]" << endl << endl;
    startTest(sorting, 0, 100, 3);
            
    out << "Массив почти отсортирован и все элементы массива - случайные значения от 0 до 100" << endl << endl;
    cout << "Массив почти отсортирован, [0; 100]" << endl << endl;
    startTest(sorting, 0, 100, 4);
            
    out << "Массив отсортирован по убыванию и все элементы массива - случайные значения от 0 до 100" << endl << endl;
    cout << "Массив отсортирован по убыванию, [0; 100]" << endl << endl;
    startTest(sorting, 0, 100, 5);
}    

void main() {
    setlocale(LC_ALL, "Russian");
    
    test("Сортировка пузырьком", bubbleSort);
    test("Сортировка пузырьком с численным условием", bubbleSort_integerCondition);
    test("Сортировка пузырьком с булевым условием", bubbleSort_booleanCondition);
    test("Сортировка вставками", insertionSort);
    test("Сортировка бинарными вставками", binaryInsertionSort);
    test("Сортировка подсчетом", countingSort, false, false);
    test("Цифровая сортировка (16-ричная система счисления)", radixSort_16, false);
    test("Сортировка слияением", mergeSort);
    test("Пирамидальная сортировка", heapSort);
    test("Быстрая сортировка (Разделитель - центральный элемент)", quickSort_middleSeparator);
    test("Быстрая сортировка (Разделитель - второй слева элемент)", quickSort_secondSeparator); 
    test("Быстрая сортировка (Разделитель - случайный элемент)", quickSort_randomSeparator); 

    cout << endl << "Подсчет времени окончен." << endl << "Результат в файле results.txt" << endl;
    out.close();
    system("pause");
}