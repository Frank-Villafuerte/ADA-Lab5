#include "AdjList.h"
#include "ShortestPath.h"
#include "Util.h"
#include <iostream>
using namespace std;

void PrintPath(vector<Edge> prevEdge, int index, int& totalWeight)
{
    if (prevEdge[index].v == prevEdge[index].w)
        cout << (char)(prevEdge[index].v+65);
    else
    {
        PrintPath(prevEdge, prevEdge[index].v,totalWeight);
        totalWeight += prevEdge[index].weight;
        cout << "->" << (char)(prevEdge[index].w+65) ;
    }
        
}
int main()
{
    vector<Edge> edges;
    GraphData graphData(8, 15, false);//8 vertices 15 aristas y no dirigido
    Range weightRange(1,10);//pesos entre 1 y 10 incluidos
    AdjList list(graphData.vertexNum,graphData.isDirected);
    Util::CreateRandomGraph(graphData,weightRange,edges);
    list.LoadEdges(edges);
    list.Export("graph.txt");
    vector<Edge> prevEdge;//aristas previas
    ShortestPath::Dijkstra(list, 2, prevEdge);
    for (int i = 0;i < prevEdge.size();i++)//imprimir caminos
    {
        int totalWeight=0;
        PrintPath(prevEdge,i, totalWeight);
        cout << " - Total: " << totalWeight;
        cout << endl;
    }
    return 1;
}