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
        cout << "������ �������: " << "\t\t" << length << endl; 
    
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
        cout << "������� ����� ����������: " << "\t" << (totalTime / testCount) << " ��" << endl; 
        cout << "����������� ����� ����������: " << "\t" << minTime << " ��" << endl;
        cout << "������������ ����� ����������: " << "\t" << maxTime << " ��" << endl << endl; 
        

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
        out << "������ �� ������������ � ��� �������� ������� - ��������� �������� �� -2 �� 2" << endl << endl;
        cout << "������ �� ������������, [-2; 2]" << endl << endl;
        startTest(sorting, -2, 2);
    } else {
        out << "������ �� ������������ � ��� �������� ������� - ��������� �������� �� 0 �� 4" << endl << endl;
        cout << "������ �� ������������, [0; 4]" << endl << endl;
        startTest(sorting, 0, 4);
    }
    
    if (allowMax) {
        out << "������ �� ������������ � ��� �������� ������� - ��������� �������� �� 0 �� INT_MAX" << endl << endl;
        cout << "������ �� ������������, [0; INT_MAX]" << endl << endl;
        startTest(sorting, 0, INT_MAX);
    }        

    out << "������ ������������ � ��� �������� ������� - ��������� �������� �� 0 �� 100" << endl << endl;
    cout << "������ ������������, [0; 100]" << endl << endl;
    startTest(sorting, 0, 100, 3);
            
    out << "������ ����� ������������ � ��� �������� ������� - ��������� �������� �� 0 �� 100" << endl << endl;
    cout << "������ ����� ������������, [0; 100]" << endl << endl;
    startTest(sorting, 0, 100, 4);
            
    out << "������ ������������ �� �������� � ��� �������� ������� - ��������� �������� �� 0 �� 100" << endl << endl;
    cout << "������ ������������ �� ��������, [0; 100]" << endl << endl;
    startTest(sorting, 0, 100, 5);
}    

void main() {
    setlocale(LC_ALL, "Russian");
    
    test("���������� ���������", bubbleSort);
    test("���������� ��������� � ��������� ��������", bubbleSort_integerCondition);
    test("���������� ��������� � ������� ��������", bubbleSort_booleanCondition);
    test("���������� ���������", insertionSort);
    test("���������� ��������� ���������", binaryInsertionSort);
    test("���������� ���������", countingSort, false, false);
    test("�������� ���������� (16-������ ������� ���������)", radixSort_16, false);
    test("���������� ���������", mergeSort);
    test("������������� ����������", heapSort);
    test("������� ���������� (����������� - ����������� �������)", quickSort_middleSeparator);
    test("������� ���������� (����������� - ������ ����� �������)", quickSort_secondSeparator); 
    test("������� ���������� (����������� - ��������� �������)", quickSort_randomSeparator); 

    cout << endl << "������� ������� �������." << endl << "��������� � ����� results.txt" << endl;
    out.close();
    system("pause");
}