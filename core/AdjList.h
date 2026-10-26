#pragma once
#include "types.h"
#include <vector>
#include <string>
class AdjList
{
private:
	std::vector<std::vector<Edge>> mList;
	int mVertexNum;
	bool isDirected;
public:
	AdjList(int theVertexNum,bool isDirected_=false);
	int GetVertexNum();
	bool AddEdge(Edge theEdge);
	void GetEdgesByIdx(int vertexIdx, std::vector<Edge>& outputEdgeList);
	void LoadEdges(std::vector<Edge> theEdges);
	void Print();
	void Export(std::string filename);

};