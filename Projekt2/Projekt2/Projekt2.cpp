// Projekt2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GenerateGraph.h"
#include "Operation.h"


int main()
{
	Operation o;
	o.readStructure();
	o.makeNeighborList1();
	o.dijkstr(o.startowy);
	cout << endl;
	o.makeMatrixLadnyKotek();
	o.dijkstrM(o.startowy);

    return 0;
}

