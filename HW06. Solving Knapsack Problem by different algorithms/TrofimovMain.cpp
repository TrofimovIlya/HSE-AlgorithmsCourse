/*
    ������ �� �������� �������
    ��������: �������� ����
    ������: 272(2)
*/

#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <omp.h>

#include "TrofimovMethods.h"

void main() {
    setlocale(LC_ALL, "Russian");

    ifstream in("input.txt");
    ofstream out("output.txt");
    out.close();

    int numberOfTests;
    in >> numberOfTests;
    int *weight;
    int *cost;

    for (int i = 0; i < numberOfTests; i++) {
        int maxWeight;
        in >> maxWeight;
        int numberOfItems;
        in >> numberOfItems;

        weight = new int[numberOfItems];
        cost = new int[numberOfItems];

        for (int j = 0; j < numberOfItems; j++) {
            in >> weight[j];
        }

        for (int j = 0; j < numberOfItems; j++) {
            in >> cost[j];
        }

        out.open("output.txt", std::ios_base::app);
        cout << "���� " << i + 1 << ":" << endl;
        out << "���� " << i + 1 << ":" << endl;

        cout << "������ ��������:" << endl;
        out << "������ ��������:" << endl;
        out.close();
        greedyPacking(weight, cost, maxWeight, numberOfItems);

        out.open("output.txt", std::ios_base::app);
        cout << "������������ ����������������:" << endl;
        out << "������������ ����������������:" << endl;
        out.close();
        dynamicProgrammingAlgorithm(weight, cost, maxWeight, numberOfItems);

        out.open("output.txt", std::ios_base::app);
        cout << "� ���������:" << endl;
        out << "� ���������:" << endl;
        out.close();
        �omebackPacking(weight, cost, maxWeight, numberOfItems);

        delete [] weight;
        delete [] cost;
    }

    system("pause");
}