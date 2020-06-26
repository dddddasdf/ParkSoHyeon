#pragma once
#include "Slot.h"

enum COMPARE
{
	COMPARE_SMALL,
	COMPARE_EQUALL,
	COMPARE_LARGE
};

struct Node
{
	Slot Data;
	Node *Next;
	Node *Previous;
};

struct List
{
	Node *HeadNode;
	Node *CurrentNode;
	int iNumberOfData;
	int (*CompareFunction)(int, int);
};

void ListInit(List *ListTmp);

void ListInsert(List *ListTmp, Slot SlotTmp);
void FirstInsert(List *ListTmp, Slot SlotTmp);
void SecondInsert(List *ListTmp, Slot SlotTmp);

bool ListFirst(List *ListTmp, Slot *SlotTmp);
bool ListSecond(List *ListTmp, Slot *SlotTmp);