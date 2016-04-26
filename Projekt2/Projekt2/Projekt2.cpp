// Projekt2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GenerateGraph.h"
#include "Operation.h"


int main()
{
	GenerateGraph g(10, 80);
	Operation o;
	/*o.readStructure();
	cout << "robi makeY" << endl;
	o.makeY();
	cout << "robi Matrix dla nie skierowanej" << endl;
	o.makeMatrix1();
	cout << "prim dla nei skierowanej na macierzy" << endl;
	o.primM();
	cout << "robi liste sasiadow" << endl;
	o.makeNeighborListD();
	cout << "prim dla nei skierowanej na liscie" << endl;
	o.primLD();
	cout << "robi macierz dla skierowanej" << endl;
	o.makeMatrixLadnyKotek();
	cout << "djisy dla macierzy" << endl;
	o.dijkstrM(o.startowy);
	cout << "robi liste sasiadow pod djstry" << endl;
	o.makeNeighborList1();
	cout << "djistry pod liste sasiectw" << endl;
	o.dijkstr(o.startowy);*/
	o.readStructure();
	o.makeY();
	o.makeNeighborList1(); // TO PORAWIAM ¯EBY BY£O NIE Z PLIKU 
	o.printNeighbourList1();





    return 0;
}

