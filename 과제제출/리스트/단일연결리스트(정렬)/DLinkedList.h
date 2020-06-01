#include "Point.h"
#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#define TRUE		1 // '��'�� ǥ���ϱ� ���� ��ũ�� ����
#define FALSE		0 // '����'�� ǥ���ϱ� ���� ��ũ�� ����

typedef Point* LData; // LData�� ���� typedef ���� - int��

typedef struct _node
{
	LData data;
	struct _node *Next;
}Node;

typedef struct _linkedlist
{
	Node *Head;
	Node *Current;
	Node *Previous;
	int NumberOfData;

	int (*Compare)(int, int);
}LinkedList;

typedef LinkedList List;

void ListInit(List* plist); // �ʱ�ȭ
void SetSortRule(List *plist, int(*Compare)(LData D1, LData D2));
void LInsert(List* plist, LData data); // ������ ����
void SInsert(List* plist, LData data);	//������ ����-����

int LFirst(List* plist, LData* data); // ù ������ ����
int LNext(List* plist, LData* data); // �� ��° ���� ������ ����

LData LRemove(List* plist); // ������ ������ ����
int LCount(List* plist); // ����� �������� �� ��ȯ

#endif
