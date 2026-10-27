#include "AdjMatrix.h"
#include <iostream>
#include <fstream>

using namespace std;

AdjMatrix::AdjMatrix(int theVertexNum,bool isDirected_)
{
    mVertexNum = theVertexNum;
    vector<int> row;
    row.resize(theVertexNum,INFINITE);
    mMatrix.resize(theVertexNum, row);
    isDirected = isDirected_;
}
int AdjMatrix::GetVertexNum()
{
    return mVertexNum;
}
int AdjMatrix::GetEdgeWeight(int theVertex1, int theVertex2)
{
    if (theVertex1 >= mVertexNum || theVertex2 >= mVertexNum)
    {
        cout << "[ERR] AdjMatrix.GetEdge: Fuera de rango" << endl;
        return INFINITE;
    }
    return mMatrix[theVertex1][theVertex2];
}

bool AdjMatrix::AddEdge(Edge theEdge)
{
    if (theEdge.v == theEdge.w)
    {
        cout << "[ERR] AdjMatrix.AddEdge: Vértice autoconectado" << endl;
        return false;
    }
    if (theEdge.v >= mVertexNum || theEdge.w >= mVertexNum)
    {
        cout << "[ERR] AdjMatrix.AddEdge: Fuera de rango" << endl;
        return false;
    }
    if (mMatrix[theEdge.v][theEdge.w] != INFINITE)
    {
        cout << "[ERR] AdjMatrix.AddEdge: Arista ya existe."<<theEdge.v<<"," << theEdge.w << endl;
        return false;
    }
    mMatrix[theEdge.v][theEdge.w] = theEdge.weight;
    if(!isDirected)
        mMatrix[theEdge.w][theEdge.v] = theEdge.weight;
    return true;
}
bool AdjMatrix::SetEdge(Edge theEdge)
{
    if (theEdge.v >= mVertexNum || theEdge.w >= mVertexNum)
    {
        cout << "[ERR] AdjMatrix.AddEdge: Fuera de rango" << endl;
        return false;
    }
    mMatrix[theEdge.v][theEdge.w] = theEdge.weight;
    if (!isDirected)
        mMatrix[theEdge.w][theEdge.v] = theEdge.weight;
    return true;
}
void AdjMatrix::GetUnconnectedIdx(std::vector<int>& theOutUnconnected)
{
    theOutUnconnected.clear();
    
    for (int i = 0;i < mVertexNum;i++)
    {
        int colMax = isDirected ? mVertexNum : i;
        for (int j = 0;j < colMax;j++)
        {
            if (i != j && mMatrix[i][j] == INFINITE)
            {
                theOutUnconnected.push_back(i * mVertexNum + j);
            }
        }
    }
}

void AdjMatrix::LoadEdges(std::vector<Edge> theEdges)
{
    for (Edge e:theEdges)
        AddEdge(e);
}

void AdjMatrix::Print()
{
    for (int i = 0;i < mVertexNum;i++)
    {
        for (int j = 0;j < mVertexNum;j++)
        {
            cout << (mMatrix[i][j] == INFINITE ? "INF" :to_string(mMatrix[i][j])) << ",";
        }
        cout << endl;
    }
}

void AdjMatrix::Export(string theFilename)
{
    ofstream file(theFilename);
    vector<string> lines;
    lines.push_back(to_string(mVertexNum)+" ");
    int edgeCount=0;
    for (int i = 0;i < mVertexNum;i++)
    {
        int maxCol = isDirected ? mVertexNum : i;
        for (int j = 0;j < maxCol;j++)
        {
            int weight = mMatrix[i][j];
            if (weight != INFINITE)
            {

                if (mVertexNum < 27)
                    lines.push_back(string(1, (char)(i + 65)) + " " + string(1, (char)(j + 65)) + " " + to_string(weight) + "\n");
                else
                    lines.push_back(to_string(i) + " " + to_string(j) + " " + to_string(weight) + "\n");
                edgeCount++;
            }
        }
    }
    lines[0] += to_string(edgeCount)+"\n";
    if (file.is_open()) {

        for (string line : lines)
            file << line;

        file.close();
        //cout << "Archivo escrito correctamente:" <<theFilename<< endl;
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

