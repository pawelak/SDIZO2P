// projekt2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GenerateGraph.h"
#include "Operation.h"
#include "MENU.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>


LARGE_INTEGER startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}

LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}


int main()
{
	/*GenerateGraph g(5, 50);
	Operation a;
	a.readStructure("plik.txt");
	cout << endl;
	a.makeY();
	a.makeNeighborListPrim();
	a.printListPrim();
	a.makeNeighborListDijkstry();
	a.printListDjikstry();
	a.makeMatrixPrim();
	a.printMatrixPrim();
	a.makeMatrixDjistry();
	cout << endl;
	a.printMatrixDjikstry();
	a.primMatrix();
	a.printPrimM();
	a.primList();
	a.printPrimL();
	a.dijkstryL(a.startowy);
	a.dijkstryM(a.startowy);
*/


//-------------------------- teraz menu-------------------
	//MENU menu;
	//menu.MENU1();

//--------------------------testy---------------------------

	LARGE_INTEGER CountStart, CountEnd, freq, timeOperation;

	srand(time(NULL));

	int sekundadzielnik = 1000000;
	int ilerazy = 100;
	int g, ileW;
	string gdzie = "result.txt";

	fstream plik;
	plik.open(gdzie, ios::out | ios::trunc);


////---------------------testy dla prima na liœcie--------------------------
//	g = 25;
//
//	for (int a = 0; a < 4; a++)
//	{
//		ileW = 40;
//		for (int i = 0; i < 5; i++)
//		{
//			plik << "\n" << to_string(ileW) + " " << to_string(g) << "\n";
//			for (int j = 0; j < ilerazy; j++)
//			{
//				GenerateGraph gr(ileW, g);
//				Operation o;
//				o.readStructure("plik.txt");
//				o.makeY();
//				o.makeNeighborListPrim();
//				CountStart = startTimer();
//
//				o.primList();
//
//				CountEnd = endTimer();
//				timeOperation.QuadPart = CountEnd.QuadPart - CountStart.QuadPart;
//				QueryPerformanceFrequency(&freq);
//				double tm = ((double)timeOperation.QuadPart)*sekundadzielnik / freq.QuadPart;
//
//				std::string str = std::to_string(tm);
//				plik << str << " ";
//			}
//			ileW += 20;
//		}
//		g += 25;
//		if (g == 100)g--;
//	}
//plik.close();
////-----------------------

////---------------------testy dla prima na macierzy--------------------------
//g = 25;
//
//for (int a = 0; a < 4; a++)
//{
//	int ileW = 40;
//	for (int i = 0; i < 5; i++)
//	{
//		plik << "\n" << to_string(ileW) + " " << to_string(g) << "\n";
//		for (int j = 0; j < ilerazy; j++)
//		{
//			GenerateGraph gr(ileW, g);
//			Operation o;
//			o.readStructure("plik.txt");
//			o.makeY();
//			o.makeMatrixPrim();
//			CountStart = startTimer();
//
//			o.primMatrix();
//
//			CountEnd = endTimer();
//			timeOperation.QuadPart = CountEnd.QuadPart - CountStart.QuadPart;
//			QueryPerformanceFrequency(&freq);
//			double tm = ((double)timeOperation.QuadPart)*sekundadzielnik / freq.QuadPart;
//
//			std::string str = std::to_string(tm);
//			plik << str << " ";
//		}
//		ileW += 20;
//	}
//	g += 25;
//	if (g == 100)g--;
//}
//plik.close();
////-----------------------


////---------------------testy dla djikstry na liœcie--------------------------przestaw losowanie!!!!
//g = 25;
//
//for (int a = 0; a < 4; a++)
//{
//	int ileW = 40;
//	for (int i = 0; i < 5; i++)
//	{
//		plik << "\n" << to_string(ileW) + " " << to_string(g) << "\n";
//		for (int j = 0; j < ilerazy; j++)
//		{
//			GenerateGraph gr(ileW, g);
//			Operation o;
//			o.readStructure("plik.txt");
//			o.makeY();
//			o.makeNeighborListDijkstry();
//
//			CountStart = startTimer();
//
//			o.dijkstryL(o.startowy);
//
//			CountEnd = endTimer();
//			timeOperation.QuadPart = CountEnd.QuadPart - CountStart.QuadPart;
//			QueryPerformanceFrequency(&freq);
//			double tm = ((double)timeOperation.QuadPart)*sekundadzielnik / freq.QuadPart;
//
//			std::string str = std::to_string(tm);
//			plik << str << " ";
//		}
//		ileW += 20;
//	}
//	g += 25;
//	if (g == 100)g--;
//}
//plik.close();
//
//plik.close();
////-----------------------


//---------------------testy dla djikstry na macierzy--------------------------przestaw losowanie!!!!
g = 25;

for (int a = 0; a < 4; a++)
{
	int ileW = 40;
	for (int i = 0; i < 5; i++)
	{
		plik << "\n" << to_string(ileW) + " " << to_string(g) << "\n";
		for (int j = 0; j < ilerazy; j++)
		{
			GenerateGraph gr(ileW, g);
			Operation o;
			o.readStructure("plik.txt");
			o.makeY();
			o.makeMatrixDjistry();
			CountStart = startTimer();

			o.dijkstryM(0);

			CountEnd = endTimer();

			timeOperation.QuadPart = CountEnd.QuadPart - CountStart.QuadPart;
			QueryPerformanceFrequency(&freq);
			double tm = ((double)timeOperation.QuadPart)*sekundadzielnik / freq.QuadPart;

			std::string str = std::to_string(tm);
			plik << str << " ";
		}
		ileW += 20;
	}
	g += 25;
	if (g == 100)g--;
}
plik.close();
//-----------------------


	return 0;
}

