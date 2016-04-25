#pragma once
class GenerateGraph
{
private:
	int maxWeight, minE, edges, nodes;
	double maxE;
	int **result;


public:
	GenerateGraph();
	GenerateGraph(int nodes, float density);
	~GenerateGraph();
};

