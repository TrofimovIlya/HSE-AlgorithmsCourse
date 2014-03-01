/*
*	Трофимов Илья
*	272ПИ/2
*	2 ноября 2013
*/

#include <iostream>
#include <time.h>
#include <ctime>
#include <Windows.h>
#include <WinBase.h>
#pragma comment (lib, "Winmm.lib")
#pragma comment (lib, "Kernel32.lib")

using namespace std;

int main()
{
	setlocale(LC_ALL,"Russian");

	// clock()
	cout << "clock()" << endl;
	double time1;
	double time2;
	for (int i = 0; i < 10; i++) {
		time1 = clock(); 
		while (clock() == time1) {
			time2 = clock(); 
		}
		cout << time1 << "мс " << time2 << "мс " << time2 - time1 << "мс" << endl; 
	}

	// time()
	cout << endl << endl << "time()"  << endl;
	time_t StartTime1, ElapsedTime1; 
	for(int i = 0; i < 10; i++) { 
		time1 = clock(); 
		StartTime1 = time(NULL);

		while (time(NULL) == StartTime1) {
			time2 = clock(); 
		}
		ElapsedTime1 = time(NULL) - StartTime1;

		cout << time1 << "мс\t" << time2 << "мс\t" << 
			time2 - time1 << "мс\t" << StartTime1 << "\t" << ElapsedTime1 << endl;
	} 

	// timeGetTime()
	cout << endl << endl << "timeGetTime()" << endl; 
	DWORD Start, Elapsed;
	for(int i = 0; i < 10; i++) {
		time1 = clock(); 
		Start = timeGetTime(); 
		while (timeGetTime() == Start); 
			time2 = clock(); 
		Elapsed = timeGetTime() - Start; 

		cout << time1 << "мс\t" << time2 << "мс\t" << time2 - time1 << "мс\t" << Start << "\t" << Elapsed << endl; 
	}

	// queryPerformanceCounter()
	cout << endl << endl << "queryPerformanceCounter()" << endl;
	LARGE_INTEGER Fr, StT, FT, TT; 
	QueryPerformanceFrequency(&Fr); 
	QueryPerformanceCounter(&StT); 
	QueryPerformanceCounter(&FT);
	while (FT.QuadPart == StT.QuadPart)
		QueryPerformanceCounter(&FT); 
	cout << "Fr\t" << Fr.QuadPart << " \tГерц" << endl; 
	cout << "FT\t" << FT.QuadPart << " \tTicks" << endl;
	cout << "StT\t" << StT.QuadPart << " \tTicks" << endl; 

	TT.QuadPart = (FT.QuadPart - StT.QuadPart);
	cout << "TT\t" << TT.QuadPart << "\t\tTicks" << endl; 

	TT.QuadPart = TT.QuadPart * 1000000000 / Fr.QuadPart; 
	cout << "TT\t" << TT.QuadPart << "\t\tнс " << endl; 
	
	// GetTickCount()
	cout << endl << endl << "GetTickCount()" << endl;
	DWORD StartTime5, ElapsedTime5; 
	for(int i = 0; i < 10; i++) { 
		time1 = clock(); 
		StartTime5 = GetTickCount(); 
		while (GetTickCount() == StartTime5); 
			time2 = clock(); 
		ElapsedTime5 = GetTickCount() - StartTime5; 

		cout << "clock\t" << time1 << "мс\t" << time2 << "мс\t" <<
			time2 - time1 << "мс" << endl; 
		cout << "getTickCount = " << StartTime5 << "\t" << 
			ElapsedTime5 << endl; 
	}

	// Assembler 32
	cout << endl << "Ассамблер 32 бита" << endl;
	for(int i = 0; i < 10; i++) { 
		time1 = clock(); 
		DWORD StartTime3, ElapsedTime3; 
		_asm { 
			RDTSC 
			mov StartTime3, eax 
		} 
		_asm { 
			RDTSC 
			sub eax, StartTime3 
			mov ElapsedTime3, eax 
		} 
		time2 = clock(); 

		cout << "32 бита\t" << StartTime3 << "t" << ElapsedTime3 << " ns" << endl; 
	}

	// Assembler 64
	cout << "Ассамблер 64 бита" << endl << endl;
	__int64 StartTime4, EndTime4; 
	for(int i = 0; i < 10; i++) { 
		time1 = clock(); 
		_asm { 
			RDTSC 
			mov DWORD PTR StartTime4, eax 
			mov DWORD PTR StartTime4+4, edx 
		}  
		_asm { 
			RDTSC 
			mov DWORD PTR EndTime4, eax 
			mov DWORD PTR EndTime4+4, edx 
		} 
		time2 = clock(); 
		cout << "64 бита\t" << StartTime4 << "\t" << EndTime4 << "\t" <<
			EndTime4 - StartTime4 << " Ticks " << endl; 
	} 

	system("pause");
	return 0;
}