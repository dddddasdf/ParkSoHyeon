#pragma once
#ifndef __C_LINKED_LIST_H__
#define __C_LINKED_LIST_H__

#include "Employee.h"

#define TRUE	1
#define FALSE	0



typedef Staff* Data;

typedef struct _node
{
	Data data;
	struct _node * next;
} Node;

typedef struct _CLL
{
	Node * Tail;
	Node * Current;
	Node * before;
	Node *Today;
	int NumberOfData;
} CList;


typedef CList List;

void ListInit(List * plist);

void LInsert(List * plist, Data data);
void LInsertFront(List * plist, Data data); // �ΰ� ��ĥ�� enum�� �߰����ָ� ����

int LFirst(List * plist, Data * pdata);
int LNext(List * plist, Data * pdata);
Data LRemove(List * plist);
int LCount(List * plist);

void InitToday(List *plist);
char* ReturnName(List *plist, int Type);	//Type == 1�� ���� ���� �̸� ��ȯ, Type == 0�� ���� �̸� ��ȯ
void MoveNextDay(List *plist);
int CheckStaff(List *plist, int Date);

#endif
