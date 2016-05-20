#include "stdafx.h"
#include "Operation.h"


Operation::Operation()
{
}


void Operation::readStructure(string adr)
{
	fstream file(adr, std::ios::in);		//wczytuje mi do pomocniczej tablicy
	if (file.is_open())
	{
		file >> edges;
		file >> nodes;
		file >> startowy;
		file >> koncowy;
		x = new int *[edges];
		if (file.fail())	cout << "File error to " << endl;
		else
		{
			int source, dest, w;
			for (int i = 0; i < edges; i++)
			{
				file >> source;
				file >> dest;
				file >> w;

				if (file.fail())
				{
					cout << "File error dupa" << endl;
					break;
				}
				else
				{
					x[i] = new int[3];
					x[i][0] = source;
					x[i][1] = dest;
					x[i][2] = w;
					//cout << x[i][0] << " " << x[i][1] << " " << x[i][2] << endl;
				}
			}
		}

		file.close();
	}
	else
		cout << "File error - OPEN calekim" << endl;
}

void Operation::makeY() {

	bool *a;
	a = new bool[edges];
	for (int i = 0; i < edges; i++) a[i] = false;
	y = new int *[edges];
	for (int i = 0; i < edges; i++) y[i] = NULL;
	a[0] = true;
	for (int i = 1; i < edges; i++)
	{
		for (int j = 0; j < i; j++)
		{
			//cout << i << endl;
			//cout << x[i][0] << "==" << x[j][0] << " && " << x[i][1] << "==" << x[j][1]  << " || " << x[i][1] << "==" << x[j][0] << " && " << x[i][0] << "==" << x[j][1] << endl;
			if ((x[i][0] == x[j][0] && x[i][1] == x[j][1]) || (x[i][1] == x[j][0] && x[i][0] == x[j][1]))
			{
				a[i] = false;
				break;
			}else a[i] = true;
		}
	}

	a[0] = true;
	edgeY = 0;
	for (int i = 0; i < edges; i++) 
	{
		if (a[i] == true)
		{
			y[edgeY] = new int[3];
			y[edgeY][0] = x[i][0];
			y[edgeY][1] = x[i][1];
			y[edgeY][2] = x[i][2];
			//cout << a[i] << endl;
			//cout << x[i][0] << " " << x[i][1] << " " << x[i][2] << endl;
			edgeY++;
		}
	}
	delete[] a;
}

//robli listê s¹siedztw dla nieskierowanej
void Operation::makeNeighborListPrim()		//dziala dziêki bartek
{
	listPrim = new elList *[nodes];
	for (int i = 0; i < nodes; i++) listPrim[i] = NULL;
	for (int i = 0; i < edgeY; i++)
	{
		tmp = new elList;				//moje klasyczne dodawanie do listy urzywane jeszcze wielokronie
		tmp->n = y[i][1];
		tmp->waga = y[i][2];
		tmp->next = listPrim[y[i][0]];    // dodajemy go na pocz¹tek listy 
		listPrim[y[i][0]] = tmp;


		tmp = new elList;
		tmp->n = y[i][0];
		tmp->waga = y[i][2];
		tmp->next = listPrim[y[i][1]];
		listPrim[y[i][1]] = tmp;
		//taki myk tu jest ¿e z logiki grafu nie skierowanego wynika a s¹siad b to b s¹siad a czyli mamy to w strony
	}
}

//wypisuje
void Operation::printListPrim()
{									//zwykle drukowanie w zasadzie nie potrzebne
	for (int i = 0; i <  nodes; i++)
	{
		cout << "A[" << i << "] =" << setw(6) << y[i][0] << " " << y[i][1] << " (" << y[i][2] << ")" << endl;
	}
}

//robi listê s¹siadów dla skierowanej
void Operation::makeNeighborListDijkstry()
{											//robli liste s¹siadów dla grafu skierowanego 
	ListDjikstry = new elList *[nodes];
	//cout << nodes << " " << edges << endl;
	for (int i = 0; i < nodes; i++) ListDjikstry[i] = NULL;
	for (int i = 0; i < edges; i++)
	{
		tmp = new elList;
		tmp->n = x[i][1];
		tmp->waga = x[i][2];
		tmp->next = ListDjikstry[x[i][0]];
		ListDjikstry[x[i][0]] = tmp;
	}
}

//drukarz do listy skierowanej
void Operation::printListDjikstry()
{									//zwykle drukowanie w zasadzie nie potrzebne
	for (int i = 0; i < edgeY; i++)
	{
		cout << "A[" << i << "] =" << setw(6) << x[i][0] << " " << x[i][1] << " (" << x[i][2] << ")" << endl;
	}
}


//robi macierz dla nieskierowanych
void Operation::makeMatrixPrim()
{
	matrixPrim = new int *[nodes];
	for (int i = 0; i < nodes; i++) {
		matrixPrim[i] = new int[nodes];
	}
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < nodes; j++) {
			matrixPrim[i][j] = 0;
		}
	}
	for (int i = 0; i < edgeY; i++)
	{
		matrixPrim[y[i][0]][y[i][1]] = y[i][2];
		matrixPrim[y[i][1]][y[i][0]] = y[i][2];
	}
}

//drukarz macierzy prima
void Operation::printMatrixPrim()
{
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			cout << setw(4) << matrixPrim[i][j];
		}
		cout << endl;
	}
}

//robi macierz dla skierowanych
void Operation::makeMatrixDjistry()
{
	matrixDjistry = new int *[nodes];
	for (int i = 0; i < nodes; i++) {		//proces tworzenia macierzy
		matrixDjistry[i] = new int[nodes];
	}
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < nodes; j++) {	//robi z niej zera po ca³oœci
			matrixDjistry[i][j] = 0;
		}
	}

	for (int i = 0; i < edges; i++)
	{
		matrixDjistry[x[i][0]][x[i][1]] = x[i][2];	//to robi zapis
	}
}

//drukuje skierowan¹
void Operation::printMatrixDjikstry()
{
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			cout << matrixDjistry[i][j] << " ";
		}
		cout << endl;
	}
}

//operacje prima dla macierzy 
void Operation::primMatrix()	//do zamiany pamiêtanie
{
	resultPrimMatrix = new int*[nodes - 1];

	bool *visited;
	visited = new bool[nodes];
	for (int i = 0; i < nodes; i++)	visited[i] = false;

	int currentNodes = y[0][0];
	vector <int> rememberedNodes;
	rememberedNodes.push_back(currentNodes);


	int idx, idy, nWaga;
	idy = currentNodes;
	idx = currentNodes;

	visited[currentNodes] = true;

	for (int i = 0; i < nodes; i++)
	{
		currentNodes = rememberedNodes[0];				//co su¿y obieg ustawia bierz¹cy na pierwszy wêze³ pamiêtany
		nWaga = INT32_MAX;								//resetuje wagê (bo musi znaleŸæ najmniejsz¹)
		for (int j = 0; j < rememberedNodes.size(); j++)
		{
			currentNodes = rememberedNodes[j];			//j obraca po pamiêtanych wêz³ach które juz by³yi tu po koleju je ustawia
			for (int k = 0; k < nodes; k++)
			{
				if (matrixPrim[currentNodes][k] != 0 && matrixPrim[currentNodes][k] < nWaga && visited[k] == false)
				{
					idx = k;
					idy = currentNodes;
					nWaga = matrixPrim[currentNodes][k];

				}
			}
		}
		resultPrimMatrix[i] = new int[3];		//wciska do wyników rezultat
		resultPrimMatrix[i][0] = idy;
		resultPrimMatrix[i][1] = idx;
		resultPrimMatrix[i][2] = nWaga;

		visited[idx] = true;					//zapamêtuje jeden wiêcej w którym by³
		rememberedNodes.push_back(idx);
	}
	delete visited;
}


//drukarz
void Operation::printPrimM()
{
	int MST = 0;
	for (int i = 0; i < nodes - 1; i++) {
		cout << "(" << resultPrimMatrix[i][0] << "," << resultPrimMatrix[i][1] << ")   " << resultPrimMatrix[i][2] << endl;
		MST += resultPrimMatrix[i][2];
	}
	cout << "MST: " << MST << endl;
}
//prim dla listy zmieniæ struct
void Operation::primList()
{
	resultPrimList = new int*[nodes - 1];

	bool *visited;
	visited = new bool[nodes];
	for (int i = 0; i < nodes; i++) visited[i] = false;

	int currentNodes = x[0][0];
	vector <int> rememberedNodes;
	rememberedNodes.push_back(currentNodes);


	int stad, tam, nWaga;
	stad = currentNodes;
	tam = currentNodes;
	visited[currentNodes] = true;

	for (int i = 0; i < nodes; i++)
	{
		currentNodes = rememberedNodes[0];
		nWaga = 11;
		for (int j = 0; j < rememberedNodes.size(); j++)
		{

			currentNodes = rememberedNodes[j];
			tmp = listPrim[currentNodes];
			while (tmp)
			{
				if (tmp->waga != 0 && tmp->waga < nWaga && visited[tmp->n] == false)
				{
					stad = currentNodes;
					tam = tmp->n;
					nWaga = tmp->waga;

				}
				tmp = tmp->next;
			}
		}
		resultPrimList[i] = new int[3];
		resultPrimList[i][0] = stad;
		resultPrimList[i][1] = tam;
		resultPrimList[i][2] = nWaga;


		visited[tam] = true;
		rememberedNodes.push_back(tam);
	}

	delete visited;
}

//drukarz dla listy po primie
void Operation::printPrimL()
{
	int MST = 0;
	for (int i = 0; i < nodes - 1; i++) {
		cout << "(" << resultPrimList[i][0] << "," << resultPrimList[i][1] << ")   " << resultPrimList[i][2] << endl;
		MST += resultPrimList[i][2];
	}
	cout << "MST: " << MST << endl;

}


void Operation::dijkstryL(int start)
{
	int i, j, u; //to do fora
	bool *visited;
	visited = new bool[nodes];
	smallestListL = new int[nodes];
	nodesListL = new int[nodes];
	for (int i = 0; i<nodes; i++)
	{
		smallestListL[i] = MAXINT;
		nodesListL[i] = -1;
		visited[i] = false;
	}
	smallestListL[start] = 0;

	for (int i = 0; i<nodes; i++)
	{
		for (j = 0; visited[j]; j++); //leci do nastêpnego nieodwiedzonego
		for (u = j++; j<nodes; j++)if (!visited[j] && (smallestListL[j]<smallestListL[u])) u = j; //tragedia z wygl¹dem ale to jest podmianka jak kozystniejsza doga

		visited[u] = true;
		for (tmp = ListDjikstry[u]; tmp; tmp = tmp->next)
			if (!visited[tmp->n] && (smallestListL[tmp->n] > smallestListL[u] + tmp->waga))
			{
				smallestListL[tmp->n] = smallestListL[u] + tmp->waga;				// weryikacja i zapis
				nodesListL[tmp->n] = u;
			}
	}


	int *licz = new int[nodes];
	/*int ile = 0;
	cout << "Startowy " << startowy << endl;
	cout << "End    Dist    Path" << endl;
	for (i = 0; i < nodes; i++)
	{
		cout << i << ": ";
		for (j = i; j > -1; j = nodesListL[j]) licz[ile++] = j;
		cout << "   | " << smallestListL[i] << " |   ";
		while (ile) cout << licz[--ile] << " ";
		cout << endl;
	}*/
	delete visited, licz;
}


void Operation::dijkstryM(int start)
{
	int i, j, u; //to do fora
	bool *visited;
	visited = new bool[nodes];
	smallestListM = new int[nodes];
	nodesListM = new int[nodes];
	for (int i = 0; i<nodes; i++)
	{
		smallestListM[i] = MAXINT;
		nodesListM[i] = -1;
		visited[i] = false;
	}
	smallestListM[start] = 0;

	for (int i = 0; i<nodes; i++)
	{
		for (j = 0; visited[j]; j++); //leci do nastêpnego nieodwiedzonego
		for (u = j++; j<nodes; j++)if (!visited[j] && (smallestListM[j]<smallestListM[u])) u = j; //tragedia z wygl¹dem ale to jest podmianka jak kozystniejsza doga

		visited[u] = true;

		for (int g = 0; g < nodes; g++)
		{
			if (matrixDjistry[u][g] != 0)
			{
				if (!visited[g] && (smallestListM[g] > smallestListM[u] + matrixDjistry[u][g]))
				{
					smallestListM[g] = smallestListM[u] + matrixDjistry[u][g];
					nodesListM[g] = u;
				}
			}
		}
	}

	int *licz = new int[nodes];
	/*int ile = 0;
	cout << "Startowy " << this->startowy << endl;
	cout << "End    Dist    Path" << endl;
	for (int i = 0; i < nodes; i++)
	{
		cout << i << ": ";
		for (j = i; j > -1; j = nodesListM[j]) licz[ile++] = j;
		cout << "   | " << smallestListM[i] << " |   ";
		while (ile) cout << licz[--ile] << " ";
		cout << endl;
	}*/
	delete visited, licz;
}



Operation::~Operation()
{
	for (int i = 0; i < edges; i++)
	{
		delete[] x[i];
		delete[] y[i];

	}
	delete x;
	x = NULL;
	delete y;
	y = NULL;

	for (int i = 0; i < nodes; i++)
	{
		//delete[] listPrim[i];
//		delete[] matrixPrim[i];
//		delete[] matrixDjistry[i];
//		delete[] ListDjikstry[i];
	}
	//delete listPrim;
	//listPrim = NULL;
	//delete matrixPrim;
	//matrixPrim = NULL;
	//delete matrixDjistry;
	//matrixDjistry = NULL;
	//delete  ListDjikstry;
	//ListDjikstry = NULL;
	//delete  matrixPrim;
	//matrixPrim = NULL;

	delete smallestListL, nodesListL, smallestListM, nodesListM;
	delete tmp, tmpDelete;

}
