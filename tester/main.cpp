#include "AdjMatrix.h"
#include "AdjList.h"
#include "ShortestPath.h"
#include <iostream>
//#include <algorithm>
#include "Util.h"
//#include "PriorityQueue.h"
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
    //A,B,C,D,E,F,G
    //0,1,2,3,4,5,6
    //PriorityQueue queue;
    vector<Edge> edges = {    // A B 6
    {2, 0, 5}, {2, 1, 1}, {1, 0, 1}, {0, 3, 1} };
    vector<Edge> edgesUnco = { {0,3,5},{2,4,5}, {0,1,7}, {1,4,7}, {1,2,8}, {1,3,9}, {5,6,11}, {3,4,15} };//disconexo
    //vector<Edge> edges = { {0,1,6} ,{0,2,1} ,{0,4,4} ,{1,2,4} ,{1,3,3} ,{2,3,2} ,{2,4,5} ,{3,5,3} ,{3,6,5} ,{4,5,3} ,{4,7,2} ,{4,8,5} ,{5,6,4} ,{5,7,2} ,{6,9,3} ,{7,8,2} ,{7,9,5} ,{8,9,4} };
    //GraphData graphData(6,20, true);
    GraphData graphData(4, 4, false);
    Range weightRange(1,10);
    AdjList list(graphData.vertexNum,graphData.isDirected);
    AdjMatrix matrix(graphData.vertexNum, graphData.isDirected);
    //Util::CreateRandomGraph(graphData,weightRange,edges);
    matrix.LoadEdges(edges);
    //matrix.Print();
    matrix.Export("matrix.txt");
    list.LoadEdges(edges);
    vector<Edge> prevEdge;
    ShortestPath::Dijkstra(list, 2, prevEdge);
    for (int i = 0;i < prevEdge.size();i++)//imprimir caminos
    {
        int totalWeight = 0;
        PrintPath(prevEdge, i, totalWeight);
        cout << " - Total: " << totalWeight;
        cout << endl;
    }
    /*if (!ShortestPath::BellmanFord(edges, graphData.vertexNum, 2, prevEdge))
    {
        cout << "ciclo negativo" << endl;
    }
    else
        cout << "correcto" << endl;
    for (int i = 0;i < prevEdge.size();i++)
    {
        Edge e = prevEdge[i];
        cout << "[" << (char)(i + 65) << "] " << (char)(e.v + 65) << "," << (char)(e.w + 65) << "," << e.weight << endl;
    }
    for (int i = 0;i < prevEdge.size();i++)
    {
        int totalWeight=0;
        PrintPath(prevEdge,i, totalWeight);
        cout << " - Total: " << totalWeight;
        cout << endl;
    }*/
    //list.LoadEdges(edges);
    //matrix.LoadEdges(edges);
    //matrix.Print();
    //matrix.Export("matrix.txt");
    //FloydWarshall(matrix);
    //matrix.Print();
    
    //list.Export("graph.txt");
    //list.Print();
    //vector<Edge> prevEdge;
    //Dijkstra(list,0,prevEdge);
    /*for (int i = 0;i < prevEdge.size();i++)
    {
        Edge e = prevEdge[i];
        cout << "[" << (char)(i+65) << "] " << (char)(e.v+65)<<","<< (char)(e.w+65) << "," << e.weight << endl;
    }*/
    //list.Export("graph.txt");
    return 1;
}