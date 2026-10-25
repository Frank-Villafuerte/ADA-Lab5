#pragma once
#include <vector>
#include "types.h"
class PriorityQueue
{
private:
	std::vector<Path> mHeap;

	void Swap(Path& edge1, Path& edge2);
	void SiftUp(int actualIdx);
	void SiftDown(int actualIdx);
public:
	void Enqueue(Path edge);
	Path Pop();
	bool IsEmpty();
	void Print();
};