#include "AdjList.h"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
AdjList::AdjList(int theVertexNum, bool isDirected_)
{
    mVertexNum = theVertexNum;
    vector<Edge> vertexConn;
    mList.resize(theVertexNum, vertexConn);//iniciar vectores vacios
    isDirected = isDirected_;
}
int AdjList::GetVertexNum()
{
    return mVertexNum;
}
bool AdjList::AddEdge(Edge theEdge)
{
    if (theEdge.v == theEdge.w)
    {
        cout << "[ERR] AdjList.AddEdge: Vértice autoconectado" << endl;
        return false;
    }
    if (theEdge.v >= mVertexNum || theEdge.w >= mVertexNum)
    {
        cout << "[ERR] AdjList.AddEdge: Fuera de rango" << endl;
        return false;
    }
    if (find(mList[theEdge.v].begin(), mList[theEdge.v].end(), theEdge)!=mList[theEdge.v].end())
    {
        cout << "[ERR] AdjList.AddEdge: Arista ya existe" << endl;
        return false;
    }
    mList[theEdge.v].push_back(theEdge);
    if (!isDirected)
        mList[theEdge.w].push_back(theEdge.Mirror());
    return true;
}
void AdjList::GetEdgesByIdx(int vertexIdx, std::vector<Edge>& outputEdgeList)
{
    outputEdgeList.clear();
    outputEdgeList= mList[vertexIdx];
}
void AdjList::LoadEdges(std::vector<Edge> theEdges)
{
    for (int i = 0;i < theEdges.size();i++)
        AddEdge(theEdges[i]);
}
void AdjList::Print()
{
    for (int i = 0;i < mList.size();i++)
    {
        cout << "["<<(char)(i + 65)<<"] ";
        for (Edge e : mList[i])
            cout << "(" << (char)(e.w+65) <<"," << e.weight << ")";
        cout << endl;
    }
}
void AdjList::Export(std::string filename)
{
    ofstream file(filename);
    vector<string> lines;
    lines.push_back(to_string(mVertexNum) + " ");
    int edgeCount = 0;
    for (int i = 0;i < mVertexNum;i++)
        for (Edge e : mList[i])
            if (e.w > i||isDirected)
            {
                if (mVertexNum < 27)
                    lines.push_back(string(1, (char)(e.v + 65)) + " " + string(1, (char)(e.w + 65)) + " " + to_string(e.weight) + "\n");
                else
                    lines.push_back(to_string(e.v) + " " + to_string(e.w) + " " + to_string(e.weight) + "\n");
                edgeCount++;
            }
    lines[0] += to_string(edgeCount) + "\n";
    if (file.is_open()) {
        for (string line : lines)
            file << line;
        file.close();
        //cout << "Archivo escrito correctamente:" <<theFilename<< endl;
    }
    else
        cout << "No se pudo abrir el archivo." << endl;
}
