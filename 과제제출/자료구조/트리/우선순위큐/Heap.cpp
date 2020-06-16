#include "Heap.h"

void HeapInit(Heap *HeapTmp, ComparePriority FunctionTmp)
{
	HeapTmp->iNumberOfData = 0;
	HeapTmp->CompareFuntion = FunctionTmp;
}

bool IsHeapEmpty(Heap *HeapTmp)
{
	if (HeapTmp->iNumberOfData == 0)
		return true;
	else
		return false;
}

int GetParentIndex(int index)
{
	return (index / 2);
}

int GetLeftChildIndex(int index)
{
	return index * 2;
}

int GetRightChildIndex(int index)
{
	return (GetLeftChildIndex(index) + 1);
}

int GetHighPriorityChildIndex(Heap *HeapTmp, int index)
{
	if (GetLeftChildIndex(index) > HeapTmp->iNumberOfData)
		return 0;

	else if (GetLeftChildIndex(index) == HeapTmp->iNumberOfData)
		return GetLeftChildIndex(index);

	else
	{
		if (HeapTmp->CompareFuntion(HeapTmp->StringArray[GetLeftChildIndex(index)],
			HeapTmp->StringArray[GetRightChildIndex(index)]) < 0)
			return GetRightChildIndex(index);
		else
			return GetLeftChildIndex(index);
	}
}


void DataInsert(Heap *HeapTmp, std::string StringTmp)
{
	int iIndex = (HeapTmp->iNumberOfData) + 1;

	while (iIndex != 1)
	{
		if (HeapTmp->CompareFuntion(StringTmp, HeapTmp->StringArray[GetParentIndex(iIndex)]) > 0)
		{
			HeapTmp->StringArray[iIndex] = HeapTmp->StringArray[GetParentIndex(iIndex)];
			iIndex = GetParentIndex(iIndex);
		}
		else
		{
			break;
		}
	}

	HeapTmp->StringArray[iIndex] = StringTmp;
	HeapTmp->iNumberOfData += 1;
}

std::string DataDelete(Heap *HeapTmp)
{
	std::string sReturnData = HeapTmp->StringArray[1];
	std::string sLastElement = HeapTmp->StringArray[HeapTmp->iNumberOfData];

	int iParentIndex = 1;
	int iChildIndex;

	while (iChildIndex = GetHighPriorityChildIndex(HeapTmp, iParentIndex))
	{
		if (HeapTmp->CompareFuntion(sLastElement, HeapTmp->StringArray[iChildIndex]) >= 0)
			break;

		HeapTmp->StringArray[iParentIndex] = HeapTmp->StringArray[iChildIndex];
		iParentIndex = iChildIndex;
	}

	HeapTmp->StringArray[iParentIndex] = sLastElement;
	HeapTmp->iNumberOfData -= 1;
	return sReturnData;
}