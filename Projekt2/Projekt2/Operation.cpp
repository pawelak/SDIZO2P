#include "stdafx.h"
#include "Operation.h"


Operation::Operation()
{

}


void Operation::readStructure()
{
	int a;
	fstream file("plik.txt", std::ios::in);
	if (file.is_open())
	{
		file >> edges;
		file >> nodes;
		file >> a;
		file >> a;
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

	



void Operation::makeNeighborList1()
{
	for (int i = 0; i < nodes; i++) neighborList1[i] = NULL;

	int a;
	fstream file("plik.txt", std::ios::in);
	if (file.is_open())
	{
		file >> edges;
		file >> nodes;
		file >> a;
		file >> a;
		neighborList1 = new elList *[nodes];
		for (int i = 0; i < nodes; i++)
			neighborList1[i] = NULL;

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

//void Operation::makeNeighborList1()
//{
//	int a;
//	fstream file("plik.txt", std::ios::in);
//	if (file.is_open())
//	{
//		file >> edges;
//		file >> nodes;
//		file >> a;
//		file >> a;
//		neighborList1 = new elList *[nodes];
//		for (int i = 0; i < nodes; i++)neighborList1[i] = NULL;
//
//		if (file.fail())	cout << "File error to " << endl;
//		else
//		{
//			int source, dest, w;
//			for (int i = 0; i < edges; i++)
//			{
//				file >> source;
//				file >> dest;
//				file >> w;
//
//				if (file.fail())
//				{
//					cout << "File error dupa" << endl;
//					break;
//				}
//				else
//				{
//					tmp = new elList;
//					tmp->n = dest;
//					tmp->waga = w;
//					neighborList1[source - 1]; //tu uci³em
//					//tmp->next = neighborList1[source];
//					//neighborList1[source] = tmp;
//					
//				}
//			}
//		}
//			
//		file.close();
//	}
//	else
//		cout << "File error - OPEN calekim" << endl;
//}
//
//void Operation::printneighborList1()
//{
//	for (int i = 0; i < nodes; i++)
//	{
//		cout << i << "    ";
//		tmp = neighborList1[i];
//		while (tmp)
//		{
//			cout << tmp->n << " ";
//		}
//		cout << endl;
//	}
//}

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

Operation::~Operation()
{
}
