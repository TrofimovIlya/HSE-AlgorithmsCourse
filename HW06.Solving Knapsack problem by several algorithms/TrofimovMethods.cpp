/* 
    Задача об упаковки рюкзака
    Выполнил: Трофимов Илья 
    Группа: 272(2)
*/

#include "TrofimovMethods.h" 

int* Weight; // Array of weights
int* Cost;  // Array of costs
int backpackMaxWeight; // Max weight of backpack
int backpackSize; // Backpack's size
int maxCost; // Max Cost
int maxWeight; // Max Weight
int* combinations; // Current combinations of taken items
int* maxCostsCombinations; // Current combinations of taken items with max cost
// Variables for time counting:
double startTime;
double finishTime; 
int** matrix; // Matrix for dynamic programming algroithm

/* 
    Greedy algorithm of packing
*/
void greedyPacking(int weight[], int cost[], int w, int n)
{ 
    // Start timer
    startTime = omp_get_wtime(); 

    // New cost per weight arraey
    double* costPerWeight = new double[n]; 
    for (int i = 0; i < n; i++) 
        costPerWeight[i] = (double)cost[i] / (double)weight[i]; 
    
    // Array with numbers of items
    int* numbers = new int[n]; 
    for (int i = 0; i < n; i ++) 
        numbers[i] = i;

    // Simple sorting arrays using costPerWeight
    for (int i = n - 1; i > 0; i--) 
        for (int j = 0; j < i; j++)
            if (costPerWeight[j] < costPerWeight[j + 1]) 
            {
                std::swap(costPerWeight[j], costPerWeight[j + 1]);
                std::swap(weight[j], weight[j + 1]);
                std::swap(cost[j], cost[j + 1]);
                std::swap(numbers[j], numbers[j + 1]);
            }

    // Array contains 1 and 0, 1 for items which should be put in backpack
    int* combinations = new int[n]; 
            
    // Filling the backpack, finding solution       
    int targetCost = 0, targetWeight = 0;
    for (int i = 0; i < n; i ++) 
    { 
        combinations[numbers[i]] = 0;
        if ((targetWeight + weight[i]) <= w) 
        {
            targetWeight = targetWeight + weight[i];
            targetCost = targetCost + cost[i];
            combinations[numbers[i]] = 1;
        }
    }   

    finishTime = omp_get_wtime();  

    printSolution(targetWeight, targetCost, combinations, n, finishTime - startTime); 
    saveSolution(targetWeight, targetCost, combinations, n, finishTime - startTime); 

    delete [] costPerWeight; 
    delete [] numbers;
    delete [] combinations;
} 

/* 
    Backtracking algorithm of packing
*/
void сomebackPacking(int weight[], int cost[], int w, int n) 
{
    // Setting up global variables
    Weight = weight; 
    Cost = cost;
    backpackMaxWeight = w;
    backpackSize = n;
    maxWeight = 0; 
    maxCost = 0;
    combinations = new int[backpackSize];
    maxCostsCombinations = new int[backpackSize];

    startTime = omp_get_wtime();

    // Start recursion
    goBack(0, 0, 0); 

    finishTime = omp_get_wtime();

    printSolution(maxWeight, maxCost, maxCostsCombinations, backpackSize, finishTime - startTime); 
    saveSolution(maxWeight, maxCost, maxCostsCombinations, backpackSize, finishTime - startTime); 

    delete [] maxCostsCombinations; 
    delete [] combinations;
}

void goBack(int i, int targetCost, int targetWeight) 
{ 
    for (int j = i; j < backpackSize; j++) 
    {
        combinations[j] = 0; 
        if (targetWeight + Weight[j] <= backpackMaxWeight) 
        { 
            if (targetCost + Cost[j] >= maxCost) 
            { 
                maxCost = targetCost + Cost[j]; // Save items
                maxCost = targetWeight + Weight[j];
                
                combinations[j] = 1; 
                for (int k = 0; k < backpackSize; k ++) 
                    maxCostsCombinations[k] = combinations[k];
            }
            
            combinations[j] = 1; 
            goBack(j + 1,  targetCost + Cost[j], targetWeight + Weight[j]); 
        } 
        combinations[j] = 0; 
    }
}

void dynamicProgrammingAlgorithm(int weight[], int cost[], int w, int n)
{
    Weight = weight; 
    Cost = cost;

    startTime = omp_get_wtime(); 
    
    matrix = new int*[n + 1]; 
    for (int i = 0; i < n + 1; i++)
        matrix[i] = new int[w + 1];

    for (int i = 0; i < w + 1; i++) 
        matrix[0][i] = 0;

    dynamicRecursion(n, w); 

    int targetWeight = 0;
    combinations = new int[n];
    for (int i = 0; i < n; i ++) 
        combinations[i] = 0;
    
    int N = n;
    int W = w;

    while (matrix[N][W] != 0) 
    { 
        if (matrix[N - 1][W] == matrix[N][W]) 
            N = N - 1;
        else 
        {
            N = N - 1;
            W = W - weight[N];
            targetWeight = targetWeight + weight[N];
            combinations[N] = 1;
        }
    }

    finishTime = omp_get_wtime();

    printSolution(targetWeight, matrix[n][w], combinations, n, finishTime - startTime); 
    saveSolution(targetWeight, matrix[n][w], combinations, n, finishTime - startTime); 
    
    for (int i = 0; i < n + 1; i++)
        delete [] matrix[i];

    delete [] matrix;
    delete [] combinations;
}

void dynamicRecursion(int i, int j) 
{
    if ((i == 0) || (j < 0))
        return;

    dynamicRecursion(i - 1, j); 
    
    matrix[i][j] = matrix[i - 1][j];
    
    if (j >= Weight[i - 1]) 
    {
        dynamicRecursion(i - 1, j - Weight[i - 1]); 
        matrix[i][j] = max(matrix[i - 1][j - Weight[i - 1]] + Cost[i - 1], matrix[i - 1][j]);
    } 
}

void printSolution(int w, int c, int combinations[], int size, double time)
{ 
    cout << "Время выполнения: " << time * 1000000 << " мкс" << endl;
    cout << "Вес рюкзака: " << w << endl; 
    cout << "Стоимость рюкзака: " << c << endl;
    cout << "Предметы в рюкзаке: ";
    for (int i = 0; i < size; i ++)
        if (combinations[i] == 1) 
            cout << i + 1 << " ";
    cout << "\n" << endl;
}

void saveSolution(int w, int c, int combinations[], int size, double time)
{ 
    ofstream out;
    out.open("output_knap.txt", std::ios_base::app);
    out << "Время выполнения: " << time * 1000000 << " мкс" << endl;
    out << "Вес рюкзака: " << w << endl; 
    out << "Стоимость рюкзака: " << c << endl;
    out << "Предметы в рюкзаке: ";
    for (int i = 0; i < size; i++)
        if (combinations[i] == 1) 
            out << i + 1 << " ";  
    out << "\n" << endl;
    out.close();
}