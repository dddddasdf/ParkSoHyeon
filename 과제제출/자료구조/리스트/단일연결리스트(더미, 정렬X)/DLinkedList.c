#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"

void ListInit(List* plist)
{
	(plist->NumberOfData) = 0; // ����Ʈ�� ����� �������� ���� 0!
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
	
	(plist->NumberOfData)++; // ����� �������� �� ����
}

int LFirst(List* plist, LData* pdata) // ù ��° ��ȸ
{
	if (plist->NumberOfData == 0) // ����� �����Ͱ� �ϳ��� ���ٸ�!
		return FALSE;

	plist->Current = plist->Head->Next;
	plist->Previous = plist->Head;

	*pdata = plist->Current->data;

	return TRUE;
}

int LNext(List* plist, LData* pdata) // �� ��° ���� ��ȸ
{
	if (plist->Current->Next == NULL) // �� �̻� ������ �����Ͱ� ���ٸ�!
		return FALSE;

	plist->Previous = plist->Current;
	plist->Current = plist->Current->Next;

	*pdata = plist->Current->data;

	return TRUE;
}

LData LRemove(List* plist)
{
	Node *DeleteNode = plist->Current;
	LData rdata = DeleteNode->data; // ������ �����͸� �ӽ÷� ����

	plist->Previous->Next = plist->Current->Next;
	plist->Current = plist->Previous;

	free(DeleteNode);
	(plist->NumberOfData)--;
	return rdata;		   // ������ �������� ��ȯ
}

int LCount(List* plist)
{
	return plist->NumberOfData;
}