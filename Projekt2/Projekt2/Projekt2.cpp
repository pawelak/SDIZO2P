// Projekt2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GenerateGraph.h"
#include "Operation.h"


int main()
{
	//GenerateGraph generateGraph(5, 80);
	Operation operation;
	operation.readStructure();
	operation.makeMatrix1();
	//operation.printMatrix1();
	//operation.primM();
	//operation.makeNeighborList1();
	//operation.printNeighbourList1();
	//operation.dijkstr(1);
	//operation.makeMatrix1();
	//operation.printMatrix1();
	//operation.makeNeighborListD();
	//operation.printListD();
	//operation.primLD();
	operation.makeY();
	operation.makeNeighborListD();
	operation.printListD();
	operation.primLD(); 
	operation.primM();

    return 0;
}

