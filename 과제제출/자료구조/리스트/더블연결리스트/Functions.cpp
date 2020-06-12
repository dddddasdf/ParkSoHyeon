#include "Functions.h"

void ListInit(List* plist)
{
	plist->Head = new Node;
	plist->Tail = new Node;

	plist->Head->Next = plist->Tail;
	plist->Head->Previous = NULL;
	plist->Tail->Next = NULL;
	plist->Tail->Previous = plist->Head;

	plist->Current = NULL;
	plist->iNumberOfData = 0;
}

void LInsert(List* plist, Data data)
{
	Node *NewNode = new Node;
	NewNode->data = data;
	NewNode->Next = NULL;
	NewNode->Previous = NULL;

	(plist->Tail->Previous)->Next = NewNode;
	NewNode->Previous = plist->Tail->Previous;
	NewNode->Next = plist->Tail;
	plist->Tail->Previous = NewNode;
	(plist->iNumberOfData)++;
}

int LFirst(List* plist, Data* pdata)
{
	if (plist->iNumberOfData == 0)
		return 0;

	plist->Current = plist->Head->Next;
	*pdata = plist->Current->data;

	return 1;
}

int LNext(List* plist, Data* pdata)
{
	if (plist->Current->Next == plist->Tail)
		return 0;

	plist->Current = plist->Current->Next;
	*pdata = plist->Current->data;

	return 1;
}

Data LRemove(List* plist)
{
	Data DataTmp;
	Node *NodeTmp = plist->Current;

	(plist->Current->Next)->Previous = plist->Current->Previous;
	(plist->Current->Previous)->Next = plist->Current->Next;
	plist->Current = plist->Current->Previous;

	DataTmp = plist->Current->data;
	delete NodeTmp;
	(plist->iNumberOfData)--;

	return DataTmp;
}

int LCount(List* plist)
{
	return (plist->iNumberOfData);
}