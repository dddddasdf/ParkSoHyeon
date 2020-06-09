#pragma once
#include "Data.h"

typedef Value *Data;

struct Node
{
	Data data;
	Node *Next;
	Node *Previous;
};

struct DBDLinkedList
{
	Node* Head;
	Node* Tail;
	Node* Current;
	int iNumberOfData;
};

typedef DBDLinkedList List;

void ListInit(List* plist);
void LInsert(List* plist, Data data);	// ������ ��带 �߰��Ѵ�.

int LFirst(List* plist, Data* pdata);
int LNext(List* plist, Data* pdata);

Data LRemove(List* plist);		// �ռ� ������ �̷��� ��带 �����Ѵ�.
int LCount(List* plist);