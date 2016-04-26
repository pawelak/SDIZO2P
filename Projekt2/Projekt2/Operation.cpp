#include "stdafx.h"
#include "Operation.h"


Operation::Operation()
{

}


void Operation::readStructure()
{
	fstream file("plik.txt", std::ios::in);
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
					//cout << x[i][0] << " " << x[i][1] << " " << x[i][2] <<  endl;
				}
			}
		}

		file.close();
	}
	else
		cout << "File error - OPEN calekim" << endl;
}

	

void Operation::makeNeighborListD()		//dziala dziêki bartek
{
	listD = new elList *[nodes];
	for (int i = 0; i < nodes; i++) listD[i] = NULL;
	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if ((x[i][0] == x[j][0] && x[i][1] == x[j][1]) || (x[i][1] == x[j][0] && x[i][0] == x[j][1]))break;
			else
			{
				tmp = new elList;    // Tworzymy nowy element
				tmp->n = x[i][1];          // Numerujemy go jako v2
				tmp->waga = x[i][2];
				tmp->next = listD[x[i][0]];    // Dodajemy go na pocz¹tek listy A[v1]
				listD[x[i][0]] = tmp;
				break;
				
			}
		}
	}
}

void Operation::printListD()
{
	for (int i = 0; i < nodes; i++)
	{
		cout << "A[" << i << "] =";
		tmp = listD[i];
		while (tmp)
		{
			cout << setw(3) << tmp->n;
			tmp = tmp->next;
		}
		cout << endl;
	}
}

void Operation::makeNeighborList1()		//dziala dziêki bartek
{
	int a;
	fstream file("plik.txt", std::ios::in);
	if (file.is_open())
	{
		file >> edges;
		file >> nodes;
		file >> a;
		file >> a;
		neighborList1 = new elList *[nodes];
		for (int i = 0; i < nodes; i++) neighborList1[i] = NULL;

		if (file.fail())
			cout << "File error to " << endl;
		else
		{
			int source, dest, w;
			for (int i = 0; i < edges; i++)
			{
				file >> source;
				file >> dest;
				file >> w;

				tmp = new elList;    // Tworzymy nowy element
				tmp->n = dest;          // Numerujemy go jako v2
				tmp->waga = w;
				tmp->next = neighborList1[source];    // Dodajemy go na pocz¹tek listy A[v1]
				neighborList1[source] = tmp;


			}
		}

		file.close();
	}
	else
		cout << "File error - OPEN calekim" << endl;
}

void Operation::printNeighbourList1()
{

	for (int i = 0; i < nodes; i++)
	{
		cout << "A[" << i << "] =";
		tmp = neighborList1[i];
		while (tmp)
	{
		cout << setw(3) << tmp->n;
		tmp = tmp->next;
	}
		cout << endl;
	}
}


void Operation::makeMatrix1()
{
	matrix1 = new int *[nodes];
	for (int i = 0; i < nodes; i++) {
		matrix1[i] = new int[nodes];
	}
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < nodes; j++) {
			matrix1[i][j] = 0;
		}
	}
	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if ((x[i][0] == x[j][0] && x[i][1] == x[j][1]) || (x[i][1] == x[j][0] && x[i][0] == x[j][1]))break;
			else
			{
				matrix1[x[i][0]][x[i][1]] = x[i][2];
				matrix1[x[i][1]][x[i][0]] = x[i][2];
			}
		}
	}
}

void Operation::primM()
{
	wynikM1 = new int*[nodes - 1];
	int aktualnyWierzcholek = x[0][0];
	vector <int> wierzcholkiDoDrzewa;
	wierzcholkiDoDrzewa.push_back(aktualnyWierzcholek);
	int help;
	bool *odwiedzone;
	odwiedzone = new bool[nodes];
	for (int i = 0; i < nodes; i++) {
		odwiedzone[i] = false;
	}
	int idx,idy, nWaga;
	idy = aktualnyWierzcholek;
	idx = aktualnyWierzcholek;
	odwiedzone[aktualnyWierzcholek] = true;

	for (int i = 0; i < nodes; i++)
	{
		aktualnyWierzcholek = wierzcholkiDoDrzewa[0];
		nWaga = 11;
		for (int j = 0; j < wierzcholkiDoDrzewa.size(); j++)
		{
			aktualnyWierzcholek = wierzcholkiDoDrzewa[j];
			for (int k = 0; k < nodes; k++)
			{
				cout << matrix1[aktualnyWierzcholek][k];
				if (matrix1[aktualnyWierzcholek][k] != 0 && matrix1[aktualnyWierzcholek][k] < nWaga && odwiedzone[k] == false)
				{
					idx = k;
					idy = aktualnyWierzcholek;
					nWaga = matrix1[aktualnyWierzcholek][k];
										
				}
			}
		}
		cout << aktualnyWierzcholek << endl;
		wynikM1[i] = new int[3];
		wynikM1[i][0] = idy;
		wynikM1[i][1] = idx;
		wynikM1[i][2] = nWaga;

		
		odwiedzone[idx] = true;
		wierzcholkiDoDrzewa.push_back(idx);
	}

	for (int i = 0; i < nodes-1; i++) {
		cout << wynikM1[i][0] << " " << wynikM1[i][1] << " " << wynikM1[i][2] << endl;
	}

}


void Operation::printMatrix1()
{
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			cout << matrix1[i][j] << " ";
		}
		cout << endl;
	}
}



//tworzy i wyswietla dijkstry, ale najpier musisz wywolac funkcje makeNeighbourList
//w makeNeighbour po tmp->n=sorce, dopisz tmp->waga=w;

void Operation::dijkstr(int start)
{
	//n-nodes
	//m-edges
	int *d, *p, *S, sptr,i,j,u;
	bool *QS;

	d = new int[nodes];
	p = new int[nodes];
	QS = new bool[nodes];
	S = new int[nodes];
	sptr = 0;

	for (int i = 0; i<nodes; i++)
	{
		d[i] = MAXINT;
		p[i] = -1;
		QS[i] = false;
		// neighborList1[i]=NULL;
	}

	cout << endl;
	d[start] = 0;

	for (int i = 0; i<nodes; i++)
	{
		for (j = 0; QS[j]; j++);
		for ( u = j++; j<nodes; j++)
			if (!QS[j] && (d[j]<d[u])) u = j;

		QS[u] = true;



		for (tmp = neighborList1[u]; tmp; tmp = tmp->next)
			if (!QS[tmp->n] && (d[tmp->n] > d[u] + tmp->waga))
			{
				d[tmp->n] = d[u] + tmp->waga;
				p[tmp->n] = u;
			}
	}

	for (i = 0; i < nodes; i++)
	{
		cout << i << ": ";

		for (j = i; j > -1; j = p[j]) S[sptr++] = j;

		while (sptr) cout << S[--sptr] << " ";

		cout << "$" << d[i] << endl;
	}
}

Operation::~Operation()
{
}
