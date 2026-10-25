#include "AdjMatrix.h"
#include "AdjList.h"
#include <iostream>
#include <algorithm>
#include "Util.h"
#include "PriorityQueue.h"
using namespace std;

int main()
{
    //A,B,C,D,E,F,G
    //0,1,2,3,4,5,6
    //PriorityQueue queue;
    vector<Edge> edges = { {0,3,5},{2,4,5},{3,5,6}, {0,1,7}, {1,4,7}, {1,2,8}, {4,5,8}, {1,3,9}, {4,6,9}, {5,6,11}, {3,4,15} };
    vector<Edge> edgesUnco = { {0,3,5},{2,4,5}, {0,1,7}, {1,4,7}, {1,2,8}, {1,3,9}, {5,6,11}, {3,4,15} };//disconexo
    int vertexNum;
    int edgeNum;
    AdjList list(7);
    AdjMatrix matrix(7);
    list.LoadEdges(edges);
    matrix.LoadEdges(edges);
    list.Print();
    matrix.Print();
    //list.Export("graph.txt");
    return 1;
}