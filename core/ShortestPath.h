#pragma once
#include "AdjList.h"
#include "AdjMatrix.h"
#include <vector>
class ShortestPath
{
private:
    static int Min(int a, int b);
    static int Plus(int a, int b);
public:
	static void Dijkstra(AdjList inputList, int startVertex, std::vector<Edge>& output);
    static void FloydWarshall(AdjMatrix& matrix);
    static bool BellmanFord(std::vector<Edge> inputList, int vertexNum, int startVertex, std::vector<Edge>& output);
};