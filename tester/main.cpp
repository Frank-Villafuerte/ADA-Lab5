#include "AdjMatrix.h"
#include "AdjList.h"
#include <iostream>
#include <algorithm>
#include "Util.h"
#include "PriorityQueue.h"
using namespace std;

//int infinite = INT_MAX;
void Dijkstra(AdjList inputList,int startVertex,vector<Edge>& output)
{
    int vertexNum = inputList.GetVertexNum();
    vector<bool> visited(vertexNum,false);
    vector <int> distances(vertexNum, INFINITE);
    vector <Edge> prevEdge(vertexNum, Edge());
    PriorityQueue queue;
    visited[startVertex] = true;
    distances[startVertex] = 0;
    queue.Enqueue(Path(startVertex,0));
    
    while (!queue.IsEmpty())
    {
        Path shortest= queue.Pop();
        vector<Edge> edgeList;
        inputList.GetEdgesByIdx(shortest.targetVertex, edgeList);
        for (Edge e : edgeList)
        {
            if (visited[e.w]) continue;
            if (distances[e.w] > distances[e.v] + e.weight)
            {
                distances[e.w] = distances[e.v] + e.weight;
                prevEdge[e.w] = e;
            }
            queue.Enqueue(Path(e.w, e.weight+distances[e.v]));
        }
        visited[shortest.targetVertex] = true;
        queue.Print();
        for (int i : distances)
            cout << (i == INFINITE ? -1 : i) << " ";
        cout << endl;
    }    
    
    output = prevEdge;
}
int Min(int a,int b)
{
    if (a > b)
    {
        return b;
    }
    return a;
}
int Plus(int a, int b)
{
    if (a==INFINITE||b==INFINITE)
    {
        return INFINITE;
    }
    return a+b;
}
void FloydWarshall(AdjMatrix& matrix)
{
    //matrix = inputMatrix;
    
    int vertexNum = matrix.GetVertexNum();
    for (int i = 0;i < vertexNum;i++)
    {
        matrix.SetEdge(Edge(i,i,0));
    }
    matrix.Print();
    for (int k = 0;k < vertexNum;k++)
    {
        for (int i = 0;i < vertexNum;i++)
            for (int j = 0;j < vertexNum;j++)
                matrix.SetEdge(Edge(i, j, Min(matrix.GetEdgeWeight(i, j), Plus(matrix.GetEdgeWeight(i, k), matrix.GetEdgeWeight(k, j)))));
            //{
            //    matrix.SetEdge(Edge(i, j, Min(matrix.GetEdgeWeight(i, k), matrix.GetEdgeWeight(k, j))));
                //cout<< matrix.GetEdgeWeight(i, k)<<"," matrix.GetEdgeWeight(k, j)
            //}
        matrix.Print();
        cout << endl;
    }
                
}
int main()
{
    //A,B,C,D,E,F,G
    //0,1,2,3,4,5,6
    //PriorityQueue queue;
    vector<Edge> edges = { {0,3,5},{2,4,5},{3,5,6}, {0,1,7}, {1,4,7}, {1,2,8}, {4,5,8}, {1,3,9}, {4,6,9}, {5,6,11}, {3,4,15} };
    vector<Edge> edgesUnco = { {0,3,5},{2,4,5}, {0,1,7}, {1,4,7}, {1,2,8}, {1,3,9}, {5,6,11}, {3,4,15} };//disconexo
    //vector<Edge> edges = { {0,1,6} ,{0,2,1} ,{0,4,4} ,{1,2,4} ,{1,3,3} ,{2,3,2} ,{2,4,5} ,{3,5,3} ,{3,6,5} ,{4,5,3} ,{4,7,2} ,{4,8,5} ,{5,6,4} ,{5,7,2} ,{6,9,3} ,{7,8,2} ,{7,9,5} ,{8,9,4} };
    GraphData graphData(6,20, true);
    Range weightRange(1,10);
    AdjList list(graphData.vertexNum,graphData.isDirected);
    AdjMatrix matrix(graphData.vertexNum, graphData.isDirected);
    Util::CreateRandomGraph(graphData,weightRange,edges);
    cout << edges.size()<<endl;
    list.LoadEdges(edges);
    matrix.LoadEdges(edges);
    matrix.Print();
    matrix.Export("matrix.txt");
    FloydWarshall(matrix);
    matrix.Print();
    
    //list.Export("graph.txt");
    //list.Print();
    /*vector<Edge> prevEdge;
    Dijkstra(list,0,prevEdge);
    for (int i = 0;i < prevEdge.size  ();i++)
    {
        Edge e = prevEdge[i];
        cout << "[" << (char)(i+65) << "] " << (char)(e.v+65)<<","<< (char)(e.w+65) << "," << e.weight << endl;
    }*/
    //list.Export("graph.txt");
    return 1;
}