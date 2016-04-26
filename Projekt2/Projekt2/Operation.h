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

	
	//elList **neighborList;
	int **x;
	int **matrix1;
	int **wynikM1;
	int startowy, koncowy;

	elList **listD;
	//bartek dijksty
	elList **neighborList1, *tmp, *tmpDelete;
	elList *pw, *rw;
	const int MAXINT = 2147483647;

public:
	Operation();
	void readStructure();
	void makeNeighborListD();
	void printListD();
	void makeNeighborList1();
	void printNeighbourList1();
	void makeMatrix1();
	void primM();
	void printMatrix1();
	void dijkstr(int);
	~Operation();
};

