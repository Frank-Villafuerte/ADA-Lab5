#include "ShortestPath.h"
#include "PriorityQueue.h"
#include <iostream>
using namespace std;
int ShortestPath::Min(int a, int b)
{
    if (a > b)
    {
        return b;
    }
    return a;
}
int ShortestPath::Plus(int a, int b)
{
    if (a == INFINITE || b == INFINITE)
    {
        return INFINITE;
    }
    return a + b;
}
void ShortestPath::Dijkstra(AdjList inputList, int startVertex, vector<Edge>& output)
{
    int vertexNum = inputList.GetVertexNum();
    vector<bool> visited(vertexNum, false);
    vector <int> distances(vertexNum, INFINITE);
    vector <Edge> prevEdge(vertexNum, Edge());
    PriorityQueue queue;
    distances[startVertex] = 0;
    prevEdge[startVertex] = Edge(startVertex, startVertex, 0);
    queue.Enqueue(Path(startVertex, 0));
    while (!queue.IsEmpty())
    {
        Path shortest = queue.Pop();
        if (visited[shortest.targetVertex]) continue;
        visited[shortest.targetVertex] = true;
        const vector<Edge>& edgeList=inputList.GetEdgesByIdx(shortest.targetVertex);
        for (Edge e : edgeList)
        {
            if (visited[e.w]) continue;
            if (distances[e.w] > distances[e.v] + e.weight)
            {
                distances[e.w] = distances[e.v] + e.weight;
                prevEdge[e.w] = e;
                queue.Enqueue(Path(e.w, e.weight + distances[e.v]));
            }
            
        }
    }
    output = prevEdge;
}

void ShortestPath::FloydWarshall(AdjMatrix& matrix)
{
    int vertexNum = matrix.GetVertexNum();
    for (int i = 0;i < vertexNum;i++)//diagonal =0
        matrix.SetEdge(Edge(i, i, 0));
    for (int k = 0;k < vertexNum;k++)
        for (int i = 0;i < vertexNum;i++)
            for (int j = 0;j < vertexNum;j++)
                matrix.SetEdge(Edge(i, j, Min(matrix.GetEdgeWeight(i, j), Plus(matrix.GetEdgeWeight(i, k), matrix.GetEdgeWeight(k, j)))));
}
bool ShortestPath::BellmanFord(vector<Edge> inputList, int vertexNum, int startVertex, vector<Edge>& output)
{
    vector<int> distances(vertexNum, INFINITE);
    vector<Edge> prevEdge(vertexNum, Edge());
    distances[startVertex] = 0;
    prevEdge[startVertex] = Edge(startVertex, startVertex, 0);
    for (int i = 0;i < vertexNum - 1;i++)
        for (Edge e : inputList)
        {
            if (distances[e.w] > Plus(distances[e.v], e.weight))
            {
                distances[e.w] = Plus(distances[e.v], e.weight);
                prevEdge[e.w] = e;
            }
        }
    for (Edge e : inputList)
        if (distances[e.w] > Plus(distances[e.v], e.weight))
            return false;
    output = prevEdge;
    return true;
}