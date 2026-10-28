#include "AdjMatrix.h"
#include "ShortestPath.h"
#include "Util.h"
#include <iostream>
using namespace std;
int main()
{
    vector<Edge> edges;
    GraphData graphData(6, 12, true);//8 vertices 15 aristas y dirigido
    Range weightRange(1,15);//pesos entre 1 y 15 incluidos
    AdjMatrix matrix(graphData.vertexNum,graphData.isDirected);
    Util::CreateRandomGraph(graphData,weightRange,edges);
    matrix.LoadEdges(edges);
    matrix.Export("graph.txt");
    ShortestPath::FloydWarshall(matrix);
    matrix.Print();
    return 1;
}