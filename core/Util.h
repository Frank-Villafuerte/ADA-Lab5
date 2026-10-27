#pragma once
#include <vector>
#include "types.h"

class Util
{
	static void EdgesIndex(int vertexNum, std::vector<int>& indexes);
public:
	static void CreateRandomGraph(GraphData graphData, Range weightRange, std::vector<Edge>& outEdges);

};