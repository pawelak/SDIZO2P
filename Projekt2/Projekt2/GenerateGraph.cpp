#include "stdafx.h"
#include "GenerateGraph.h"


GenerateGraph::GenerateGraph()
{

}

GenerateGraph::GenerateGraph(int nodes, float density)
{
	this->nodes = nodes;
	maxWeight = 9;
	int minE = nodes - 1;								//�eby by� graf musi mie� minium tyle to jest w zasadzie drzewo w tedy
	maxE = ((nodes - 1)*nodes) / 2;						//to jest maksymalna liczna kraw�dzi dla grafu
	int minDensity = ceil((minE / maxE) * 100);
	edges = ceil(maxE*(density / 100));					//tyle chcemy kraw�dzi
	int weight;
	result = new int *[edges];							

	if (density > minDensity && density<100)			//warunki wej�cia �eby nie robi�o niedorzcznych graf�w
	{													//tu robi drzewo rozpinaj�ce �eby by� warunek na sp�jnos� grafu 
		vector <int> tab;								// vektor co b�dzie pami�ta� czy odwiedzone
		for (int i = 0; i < nodes; i++)	tab.push_back(i);
		
		srand(time(NULL));
		int next, previous;
		previous = rand() % nodes;
		tab[previous] = -1;
		for (int i = 1; i < minE + 1; i++)
		{
			while (true)								//nie elegancki rand co losuje nam wierzcho�ki 
			{
				next = rand() % nodes;
				if (tab[next] >= 0)break;
			}

			result[i - 1] = new int[3];
			result[i - 1][0] = previous;
			result[i - 1][1] = next;
			weight = (rand() % maxWeight) + 1;
			result[i - 1][2] = weight;
			tab[next] = -1;
			previous = next;
		}											// od tego momentu do drzewa rozpinaj�ceg odopinamy losowe kraw�dzie
		bool czyJest = false;						// sprawdza czy taka kraw�d� ju� by�a bo jak by�a to s�abo
		for (int i = minE; i < edges; i++)
		{
			while (true)
			{
				czyJest = false;
				previous = rand() % nodes;
				next = rand() % nodes;
				for (int j = 0; j < i; j++)
				{
					if ((result[j][0] == previous && result[j][1] == next) || (result[j][0] == next && result[j][1] == previous) || (next == previous))
					{
						czyJest = true;
						break;
					}
				}
				if (czyJest == false)
				{
					result[i] = new int[3];
					result[i][0] = previous;
					result[i][1] = next;
					weight = rand() % maxWeight + 1;
					result[i][2] = weight;
					break;
				}
			}

		}

		for (int i = 0; i < edges; i++)	cout << result[i][0] << " " << result[i][1] << " " << result[i][2] << endl;
		tab.clear();		//chyba tak si� odopala destruktor vektora
	}
	else cout << "blendna gestosc " << endl;

	fstream plik("plik.txt", ios::out);				//wpisuje do pliku 
	if (plik.good())			
	{
		plik << nodes << " " << edges << "\n";
		for (int i = 0; i < edges; i++)	plik << result[i][0] << " " << result[i][1] << " " << result[i][2] << "\n";
		plik.close();
	}
}


GenerateGraph::~GenerateGraph()
{
	for (int i = 0; i < edges; i++)	delete result[i];
	result = NULL;
}
