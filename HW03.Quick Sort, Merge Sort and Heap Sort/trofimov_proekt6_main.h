// �������� ����, 272(2)��
// ������ 6-7. ����������� ����������

#include <iostream>
#include <fstream>

using namespace std;

void saveArrayToFile(int *array, int n, ofstream& fOut);
void printArray(int *array, int n);
void openFile();
void sort(int *array, int n);
void generateArray(int *array, int n, int min, int max);
