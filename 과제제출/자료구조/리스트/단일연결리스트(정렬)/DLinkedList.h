#include "Point.h"
#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#define TRUE		1 // '참'을 표현하기 위한 매크로 정의
#define FALSE		0 // '거짓'을 표현하기 위한 매크로 정의

typedef Point* LData; // LData에 대한 typedef 선언 - int형

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

void ListInit(List* plist); // 초기화
void SetSortRule(List *plist, int(*Compare)(LData D1, LData D2));
void LInsert(List* plist, LData data); // 데이터 저장
void SInsert(List* plist, LData data);	//데이터 저장-정렬

int LFirst(List* plist, LData* data); // 첫 데이터 참조
int LNext(List* plist, LData* data); // 두 번째 이후 데이터 참조

LData LRemove(List* plist); // 참조한 데이터 삭제
int LCount(List* plist); // 저장된 데이터의 수 반환

#endif
