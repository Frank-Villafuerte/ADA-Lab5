#include "AdjList.h"
#include "AdjMatrix.h"
#include "ShortestPath.h"
#include "Util.h"
#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;
void Print(vector<vector<float>> time, string filename)
{
    ofstream file(filename);
    if (file.is_open()) {
        file << "vertex,0.3,0.5,0.8\n";
        for (int i = 0;i < time[0].size();i++)
            file << to_string(i+4)<<"," << to_string(time[0][i]) << "," << to_string(time[1][i]) << "," << to_string(time[2][i]) << "\n";
        file.close();
        cout << "Archivo escrito correctamente."<<filename << endl;
    }
    else {
        cout << "Error al abrir el archivo." << endl;
    }
}
int main()
{
    vector<Edge> edges;
    vector<float> density = {0.3,0.5,0.8};
    vector<vector<float>> timeD(density.size());
    vector<vector<float>> timeBF(density.size());
    vector<vector<float>> timeFW(density.size());
    for (int i = 4;i <= 100;i++)
    {
        for(int j=0;j<density.size();j++)
        {
            GraphData graphData(i, i*i*density[j], true);
            Range weightRange(1, 2 * graphData.edgeNum);//pesos entre 1 y el doble de la cantidad de aristas
            Util::CreateRandomGraph(graphData, weightRange, edges);
            AdjList list(graphData.vertexNum, graphData.isDirected);
            AdjMatrix matrix(graphData.vertexNum, graphData.isDirected);
            list.LoadEdges(edges);
            matrix.LoadEdges(edges);
            vector<Edge> prevEdge;//aristas previas
            auto start= chrono::steady_clock::now();
            ShortestPath::Dijkstra(list, 2, prevEdge);
            auto end = chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<chrono::nanoseconds>(end-start);
            timeD[j].push_back(static_cast<float>(duration.count()) / 1000000);

            start = chrono::steady_clock::now();
            ShortestPath::FloydWarshall(matrix);
            end = chrono::steady_clock::now();
            duration = std::chrono::duration_cast<chrono::nanoseconds>(end - start);
            timeFW[j].push_back(static_cast<float>(duration.count()) / 1000000);

            start = chrono::steady_clock::now();
            ShortestPath::BellmanFord(edges, graphData.vertexNum, 0, prevEdge);
            end = chrono::steady_clock::now();
            duration = std::chrono::duration_cast<chrono::nanoseconds>(end - start);
            timeBF[j].push_back(static_cast<float>(duration.count()) / 1000000);
        }
    }
    Print(timeD,"dijkstra.csv");
    Print(timeBF, "bellmanford.csv");
    Print(timeFW, "floydwarshall.csv");
    return 1;
}