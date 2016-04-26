#pragma once
class Operation
{
private:
	struct elList
	{
		elList *next;
		int n, waga;
	};
	int nodes, edges;
	elList **neighborList1, *tmp, *tmpDelete;
	//elList **neighborList;
	int **x;
	int **matrix1;
	int **wynikM1;
	
	

public:
	Operation();
	void readStructure();
	void makeNeighborList1();
	void printNeighbourList1();
	void printneighborList1();
	void makeMatrix1();
	void primM();
	void printMatrix1();
	~Operation();
};

