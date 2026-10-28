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
    vector<Edge> edges =
    {
        { 0, 1, 4 },{ 1, 2, 2 },{ 2, 0, 7 },{ 0, 2, 5 },{ 2, 3, 1 },{ 3, 0, 9 },{ 1, 3, 3 }
    };
    GraphData graphData(4, 7, true);//4 vertices 7 aristas y dirigido
    AdjList list(graphData.vertexNum,graphData.isDirected);//lista creada para exportar
    list.LoadEdges(edges);
    list.Export("graph.txt");
    vector<Edge> prevEdge;//aristas previas
    if (ShortestPath::BellmanFord(edges, graphData.vertexNum, 0, prevEdge))
        for (int i = 0;i < prevEdge.size();i++)//imprimir caminos
        {
            int totalWeight = 0;
            PrintPath(prevEdge, i, totalWeight);
            cout << " - Total: " << totalWeight;
            cout << endl;
        }
    else
        cout << "Ciclo negativo" << endl;
    return 1;
}