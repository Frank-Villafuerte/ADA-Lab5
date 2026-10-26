#include "PriorityQueue.h"
#include <iostream>
using namespace std;
void PriorityQueue::Swap(Path& edge1, Path& edge2)
{
	Path aux = edge1;
	edge1 = edge2;
	edge2 = aux;
}

void PriorityQueue::Enqueue(Path edge)
{
	mHeap.push_back(edge);
	int actualPos = mHeap.size()-1;
	SiftUp(actualPos);
}

Path PriorityQueue::Pop()
{
	Path output = mHeap[0];
	mHeap[0] = mHeap[mHeap.size() - 1];
	mHeap.pop_back();
	SiftDown(0);
	return output;
}

bool PriorityQueue::IsEmpty()
{
	return mHeap.empty();
}

void PriorityQueue::SiftUp(int actualIdx)
{
	if (actualIdx == 0)
		return;
	if (mHeap[(actualIdx - 1) / 2].weight > mHeap[actualIdx].weight)
	{
		Swap(mHeap[(actualIdx - 1) / 2], mHeap[actualIdx]);
		SiftUp((actualIdx - 1) / 2);
	}
}

void PriorityQueue::SiftDown(int actualIdx)
{
	int minIdx = actualIdx;
	if (2 * (actualIdx + 1) - 1 < mHeap.size() && mHeap[minIdx].weight > mHeap[2 * (actualIdx + 1) - 1].weight)
	{
		minIdx = 2 * (actualIdx + 1) - 1;
	}
	if (2 * (actualIdx + 1) < mHeap.size() && mHeap[minIdx].weight > mHeap[2 * (actualIdx + 1)].weight)
	{
		minIdx = 2 * (actualIdx + 1);
	}

	if (minIdx !=actualIdx)
	{
		Swap(mHeap[actualIdx], mHeap[minIdx]);
		SiftDown(minIdx);
	}
	
}

void PriorityQueue::Print()
{
	for (Path e : mHeap)
		cout << (e.weight==INFINITE?0:e.weight) << " ";
	cout << endl;
}
