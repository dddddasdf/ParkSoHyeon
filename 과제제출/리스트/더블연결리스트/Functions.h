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
void LInsert(List* plist, Data data);	// 꼬리에 노드를 추가한다.

int LFirst(List* plist, Data* pdata);
int LNext(List* plist, Data* pdata);

Data LRemove(List* plist);		// 앞서 참조가 이뤄진 노드를 삭제한다.
int LCount(List* plist);