#pragma once
#include <iostream>
#include <string>

#define HEAP_SIZE 100

typedef int ComparePriority(std::string string1, std::string string2);

struct Heap
{
	std::string StringArray[HEAP_SIZE];
	int iNumberOfData;
	ComparePriority *CompareFuntion;
};

void HeapInit(Heap *HeapTmp, ComparePriority FunctionTmp);
bool IsHeapEmpty(Heap *HeapTmp);

void DataInsert(Heap *HeapTmp, std::string StringTmp);
std::string DataDelete(Heap *HeapTmp);