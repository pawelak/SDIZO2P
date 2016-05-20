#include "stdafx.h"
#include "MENU.h"
#include "GenerateGraph.h"
#include "Operation.h"


MENU::MENU()
{
}

void MENU::MENU1()
{
	co = 0;
	do
	{
		cout << " \nWybierz strukture: (zostana one wywolane z danymi z wygenerowanego pliku)" << endl;
		cout << " 1. Generuj graf" << endl;
		cout << " 2. podaj plik z grafem " << endl;
		cin >> co;
		switch (co)
		{
		case 1:
		{
			MENUGeneruj();
			break;
		}
		case 2:
		{
			MENUGraf();
			break;
		}
		default:
			cout << "Niema takiej komendy" << endl;
			MENU1();
			break;
		}
	} while (co != 0);


}


void MENU::MENUGeneruj()
{
	int nodes, density;
	bool a = 0;

	do
	{
		cout << "Podaj ile wezlow (musi to byc liczba naturalna dodatnia) oraz gestosc grafu(w procentach, bez znaku %) (jesli widzisz komunikat ponownie oznacza to bledne cyf)" << endl;
		cin >> nodes >> density;
		if (nodes>1 && density >= 0 && density <= 100)	a = 1;
	} while (!a);


	GenerateGraph gen(nodes, density);
	cout << "wykonano pomyslnie do pliku: plik.txt" << endl;
	MENU1();

}

void MENU::MENUGraf()
{
	string adr;
	bool a = 0;
	do
	{
		cout << "Podaj nazwe pliku: (jesli widzisz to poraz kolejny to plik nie zostal znaleziony)";
		cin >> adr;
		std::ifstream file;
		file.open(adr);
		if (file.is_open())a = 1;
		file.close();
	} while (!a);

	Operation o;
	o.readStructure(adr);
	o.makeY();
	o.makeNeighborListPrim();
	o.makeMatrixPrim();
	o.makeNeighborListDijkstry();
	o.makeMatrixDjistry();
	do
	{
		cout << "\n Wybierz opcje " << endl;
		cout << " 1. Algorytm Prima dla listy " << endl;
		cout << " 2. Algorytm Prima dla macierzy " << endl;
		cout << " 3. Algorytm Djikstry" << endl;
		cout << " 4. Algorytm Djikstry dla macierzy " << endl;
		cout << " 5. Wypisz liste dla Prima" << endl;
		cout << " 6. Wypisz macierz dla Prima" << endl;
		cout << " 7. Wypisz listes dla Djiksry" << endl;
		cout << " 8. Wypisz macierz dla djikstry" << endl;
		cout << " 0. Exit " << endl;
		cin >> co;

		switch (co)
		{
		case 1:
		{
			o.primList();
			o.printPrimL();
			break;
		}
		case 2:
		{
			o.primMatrix();
			o.printPrimM();
			break;
		}
		case 3:
		{
			o.dijkstryL(o.startowy);
			break;
		}
		case 4:
		{
			o.dijkstryM(o.startowy);
			break;
		}
		case 5:
		{
			o.printListPrim();
			break;
		}
		case 6:
		{
			o.printMatrixPrim();
			break;
		}
		case 7:
		{
			o.printListDjikstry();
			break;
		}
		case 8:
		{
			o.printMatrixDjikstry();
			break;
		}
		case 0:
		{
			MENU1();
			break;
		}
		default:
			cout << "Niema takiej komendy" << endl;
			break;
		}
	} while (co != 0);

}


MENU::~MENU()
{
}
