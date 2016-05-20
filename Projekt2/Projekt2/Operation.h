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


	int edgeY;

	elList **listD;
	elList **neighborList1;




	int **x, **y, **matrixPrim, **matrixDjistry, **resultPrimMatrix, **resultPrimList, *smallestListL, *nodesListL, *smallestListM, *nodesListM;//du¿o tego ale chcialem mieæ ka¿de osobno
	elList **ListDjikstry, *tmp, *tmpDelete, **listPrim;
	const int MAXINT = 2147483647;

public:
	int startowy, koncowy;
	Operation();
	void readStructure(string adr);
	void makeY();
	void makeNeighborListPrim();
	void printListPrim();
	void makeNeighborListDijkstry();
	void printListDjikstry();
	void makeMatrixPrim();
	void printMatrixPrim();
	void makeMatrixDjistry();
	void printMatrixDjikstry();
	void primMatrix();
	void printPrimM();
	void primList();
	void printPrimL();
	void dijkstryL(int start);
	void dijkstryM(int start);
	~Operation();
};

