#pragma once
#include <vector>
#include <string>
#include "types.h"

//Matriz cuenta los vértices desde 0
class AdjMatrix
{
private:
    std::vector<std::vector<int>> mMatrix;
    int mVertexNum;
    bool isDirected;
public:
    AdjMatrix(int theVertexNum,bool isDirected_=false);
    int GetVertexNum();
    int GetEdgeWeight(int theVertex1, int theVertex2);
    bool AddEdge(Edge theEdge);
    bool SetEdge(Edge theEdge);
    void GetUnconnectedIdx(std::vector<int>& theOutUnconnected);
    void LoadEdges(std::vector<Edge> theEdges);
    void Print();
    void Export(std::string theFilename);
};
