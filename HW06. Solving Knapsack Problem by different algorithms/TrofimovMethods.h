#include <iostream> 
#include <Windows.h>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <omp.h>

using namespace std; 
void greedyPacking(int weight[], int cost[], int w, int n); 
void ñomebackPacking(int weight[], int cost[], int w, int n); 
void dynamicProgrammingAlgorithm(int weight[], int cost[], int w, int n);
void dynamicRecursion(int i, int j);
void goBack(int i, int targetCost, int targetWeight);
void printSolution(int w, int c, int combinations[], int size, double time);
void saveSolution(int w, int c, int combinations[], int size, double time);
