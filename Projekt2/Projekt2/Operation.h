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
	int **y;
	int **matrix1;
	int **matrix2;
	int **wynikM1;
	int **wynikLD;
	
	int edgeY;

	elList **listD;
	//bartek dijksty
	elList **neighborList1, *tmp, *tmpDelete;
	elList *pw, *rw;
	const int MAXINT = 2147483647;

public:
	int startowy, koncowy;
	Operation();
	void readStructure();
	void makeY();
	void makeNeighborListD();
	void printListD();
	void makeNeighborList1();
	void printNeighbourList1();
	void makeMatrix1();
	void makeMatrixLadnyKotek();
	void primM();
	void primLD();
	void printMatrix1();
	void dijkstr(int);
	void dijkstrM(int start);
	~Operation();
};

