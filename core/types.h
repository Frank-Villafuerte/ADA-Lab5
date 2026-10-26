#pragma once
#include <string>
const int INFINITE = INT_MAX;
struct Edge
{
	int v;
	int w;
	int weight;
	Edge() = default;
	Edge(int v_, int w_, int weight_)
	{
		v = v_;
		w = w_;
		weight = weight_;
	}
	bool operator==(Edge other)
	{
		return v == other.v && w == other.w;//grafo dirigido
	}
	Edge Mirror()
	{
		return Edge(w, v, weight);
	}
};
struct Path
{
	int targetVertex;
	int weight;
	Path() = default;
	Path(int targetVertex_, int weight_)
	{
		targetVertex = targetVertex_;
		weight = weight_;
	}
};
struct Range
{
	int min;
	int max;
	Range(int min_, int max_)
	{
		min = min_;
		max = max_;
	}
};
struct GraphData
{
	int vertexNum;
	int edgeNum;
	bool isDirected;
	GraphData(int vertexNum_, int edgeNum_, bool isDirected_)
	{
		vertexNum = vertexNum_;
		edgeNum = edgeNum_;
		isDirected = isDirected_;
	}
};