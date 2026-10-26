#include "Util.h"
#include <algorithm>
#include <iostream>

#include <chrono>
#include <random>
#include <string>
#include <fstream>
#include "AdjMatrix.h"
using namespace std;

void Util::EdgesIndex(int vertexNum,vector<int>& indexes)
{
	indexes.clear();
	for (int i = 0;i < vertexNum;i++)
	{
		for (int j = 0;j < vertexNum;j++)
			if(i!=j)
				indexes.push_back(i*vertexNum+j);
	}
}
void Util::CreateRandomGraph(GraphData graphData,Range weightRange, vector<Edge>& outEdges)
{
	outEdges.clear();
	if (graphData.edgeNum < graphData.vertexNum)
	{
		cout << "[ERR] Util.creategraph: No hay suficientes aristes para un grafo conexo";
		return;
	}
	vector<int> list;//lista de vertices
	for (int i = 0;i < graphData.vertexNum;i++)
	{
		list.push_back(i);
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(list.begin(),list.end(), std::default_random_engine(seed));
	AdjMatrix tempMatrix(graphData.vertexNum, graphData.isDirected);//matriz temporal para validar aristas
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<> distrW(weightRange.min,weightRange.max);
	uniform_int_distribution<> distrE(0, graphData.vertexNum-1);
	for (int i : list)
		cout << (char)(i+65) << " ";
	cout << endl;
	for (int i = 0;i < list.size();i++)
		tempMatrix.AddEdge(Edge(list[i], list[(i + 1) % list.size()], distrW(generator)));
	
	vector<int> unconnectedIdx;
	tempMatrix.GetUnconnectedIdx(unconnectedIdx);
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(unconnectedIdx.begin(), unconnectedIdx.end(), std::default_random_engine(seed));
	for (int i = 0;i < graphData.edgeNum-list.size()&&i<unconnectedIdx.size();i++)
	{
		tempMatrix.AddEdge(Edge(unconnectedIdx[i] / graphData.vertexNum, unconnectedIdx[i] % graphData.vertexNum, distrW(generator)));
	}
	for (int i = 0;i < graphData.vertexNum;i++)
	{
		int maxCol = graphData.isDirected ? graphData.vertexNum : i;
		for (int j = 0;j < maxCol;j++)
		{
			int weight = tempMatrix.GetEdgeWeight(i, j);
			if (weight != INFINITE)
				outEdges.push_back({i,j,weight});
		}
	}
	tempMatrix.Export("temp.txt");
	
}

int Util::Random(int min, int max)
{
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<> distr(min, max);
	return distr(generator);
}
