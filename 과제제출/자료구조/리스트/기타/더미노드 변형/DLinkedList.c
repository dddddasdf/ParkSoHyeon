#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"

void ListInit(List* plist)
{
	(plist->NumberOfData) = 0; // 리스트에 저장된 데이터의 수는 0!
	plist->Head = (Node*)malloc(sizeof(Node));
	plist->Head->Next = NULL;
	plist->Current = NULL;
}

void LInsert(List* plist, LData data)
{
	Node *NewNode = (Node*)malloc(sizeof(Node));
	NewNode->data = data;
	NewNode->Next = plist->Head->Next;
	plist->Head->Next = NewNode;
	
	(plist->NumberOfData)++; // 저장된 데이터의 수 증가
}

int LFirst(List* plist, LData* pdata) // 첫 번째 조회
{
	if (plist->NumberOfData == 0) // 저장된 데이터가 하나도 없다면!
		return FALSE;

	plist->Current = plist->Head->Next;
	plist->Previous = plist->Head;

	*pdata = plist->Current->data;

	return TRUE;
}

int LNext(List* plist, LData* pdata) // 두 번째 이후 조회
{
	if (plist->Current->Next == NULL) // 더 이상 참조할 데이터가 없다면!
		return FALSE;

	plist->Previous = plist->Current;
	plist->Current = plist->Current->Next;

	*pdata = plist->Current->data;

	return TRUE;
}

LData LRemove(List* plist)
{
	Node *DeleteNode = plist->Current;
	LData rdata = DeleteNode->data; // 삭제할 데이터를 임시로 저장

	plist->Previous->Next = plist->Current->Next;
	plist->Current = plist->Previous;

	free(DeleteNode);
	(plist->NumberOfData)--;
	return rdata;		   // 삭제된 데이터의 반환
}

int LCount(List* plist)
{
	return plist->NumberOfData;
}