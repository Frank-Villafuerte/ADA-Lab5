#include "AdjList.h"
#include "ShortestPath.h"
#include <iostream>
using namespace std;
int main()
{
    vector<Edge> edges = { {0,1,15},{0,3,60},{1,2,35},{2,4,40},{3,4,50} };
    GraphData graphData(5, 5, false);//8 vertices 15 aristas y no dirigido
    AdjMatrix matrix(graphData.vertexNum,graphData.isDirected);
    matrix.LoadEdges(edges);
    matrix.Export("graph.txt");
    ShortestPath::FloydWarshall(matrix);
    cout << "MAX PING"<<endl;
    for (int i = 0;i < graphData.vertexNum;i++)
    {
        cout << "[" << (char)(i+65) << "] ";
        int max = 0;
        for (int j = 0;j < graphData.vertexNum;j++)
        {
            int ping = matrix.GetEdgeWeight(i, j);
            if (ping > max)
                max = ping;
        }
        cout << max <<"ms" << endl;
    }
    return 1;
}