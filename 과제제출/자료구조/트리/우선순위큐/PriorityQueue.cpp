#include "PriorityQueue.h"

void PriorityQueueInit(PriorityQueue *QueueTmp, ComparePriority FunctionTmp)
{
	HeapInit(QueueTmp, FunctionTmp);
}

bool IsQueueEmpty(PriorityQueue *QueueTmp)
{
	return IsHeapEmpty(QueueTmp);
}

void EnqueuePriorityQueue(PriorityQueue *QueueTmp, std::string StringTmp)
{
	DataInsert(QueueTmp, StringTmp);
}

std::string DequeuePriorityQueue(PriorityQueue *QueueTmp)
{
	return DataDelete(QueueTmp);
}