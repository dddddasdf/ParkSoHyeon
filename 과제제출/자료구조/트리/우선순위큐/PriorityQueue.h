#pragma once
#include "Heap.h"

typedef Heap PriorityQueue;

void PriorityQueueInit(PriorityQueue *QueueTmp, ComparePriority FunctionTmp);

bool IsQueueEmpty(PriorityQueue *QueueTmp);

void EnqueuePriorityQueue(PriorityQueue *QueueTmp, std::string StringTmp);
std::string DequeuePriorityQueue(PriorityQueue *QueueTmp);