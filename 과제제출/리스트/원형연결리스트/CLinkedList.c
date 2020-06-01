#include <stdio.h>
#include <stdlib.h>
#include "CLinkedList.h"

void ListInit(List * plist)
{
	plist->Tail = NULL;
	plist->Current = NULL;
	plist->before = NULL;
	plist->Today = NULL;
	plist->NumberOfData = 0;
}

void LInsertFront(List * plist, Data data)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	if (plist->Tail == NULL)
	{
		plist->Tail = newNode;
		newNode->next = newNode;
	}
	else
	{
		newNode->next = plist->Tail->next;
		plist->Tail->next = newNode;
	}

	(plist->NumberOfData)++;
}

void LInsert(List * plist, Data data)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	if (plist->Tail == NULL)
	{
		plist->Tail = newNode;
		newNode->next = newNode;
	}
	else
	{
		newNode->next = plist->Tail->next;
		plist->Tail->next = newNode;
		plist->Tail = newNode;
	}

	(plist->NumberOfData)++;
}

int LFirst(List * plist, Data * pdata)
{
	if (plist->Tail == NULL)    // ����� ��尡 ���ٸ�
		return FALSE;

	plist->before = plist->Tail;
	plist->Current = plist->Tail->next;

	*pdata = plist->Current->data;
	return TRUE;
}

int LNext(List * plist, Data * pdata)
{
	if (plist->Tail == NULL)    // ����� ��尡 ���ٸ�
		return FALSE;

	plist->before = plist->Current;
	plist->Current = plist->Current->next;

	*pdata = plist->Current->data;
	return TRUE;
}

Data LRemove(List * plist)
{
	Node * rpos = plist->Current;
	Data rdata = rpos->data;

	if (rpos == plist->Tail)    // ���� ����� tail�� ����Ų�ٸ�
	{
		if (plist->Tail == plist->Tail->next)    // �׸��� ������ ���� �����
			plist->Tail = NULL;
		else
			plist->Tail = plist->before;
	}

	plist->before->next = plist->Current->next;
	plist->Current = plist->before;

	free(rpos);
	(plist->NumberOfData)--;
	return rdata;
}

int LCount(List * plist)
{
	return plist->NumberOfData;
}

void InitToday(List *plist)
{
	plist->Today = plist->Tail->next;
}

char* ReturnName(List *plist)
{
	return (plist->Today->data->sName);
}