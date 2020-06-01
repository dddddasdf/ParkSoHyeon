#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DLinkedList.h"
#include "Point.h"

#define LARGE 2
#define EQUAL 1
#define SMALL 0

int Standard(int NewObject, int Target)
{
	if (NewObject > Target)
		return LARGE;	//���� ������� ��尡 �� ��󺸴� Ŭ ��� �� ��ȯ
	else if (NewObject == Target)
		return EQUAL;
	else
		return SMALL;	//�ƴҽ� ���� ��ȯ
}

int main(void)
{
	List list;
	Point compPos;
	Point * ppos;

	ListInit(&list);
	SetSortRule(&list, Standard);

	/*** 4���� ������ ���� ***/
	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 4, 1);
	LInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 2, 2);
	SInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 6);
	SInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 2);
	SInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 1, 6);
	SInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 10, 2);
	SInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 1);
	SInsert(&list, ppos);

	/*** ����� �������� ��� ***/
	printf("���� �������� ��: %d \n", LCount(&list));

	if (LFirst(&list, &ppos))
	{
		ShowPointPos(ppos);

		while (LNext(&list, &ppos))
			ShowPointPos(ppos);
	}
	printf("\n");

	/*** xpos�� 2�� ��� ������ ���� ***/
	compPos.xpos = 2;
	compPos.ypos = 0;

	if (LFirst(&list, &ppos))
	{
		if (PointComp(ppos, &compPos) == 1)
		{
			//List�� ����ü�� �ּҰ��� ����� ���
			//�ּ� ���� �����Ҵ��� ����ΰ�츦 �����ؼ� �޸� �����ϴµ��� ������ �ִ�.
			//�Ҹ��� �����͸� ��ȯ�ϰ� �޸𸮸� ���� �� �� �ִ� ��ȸ�� �־���Ѵ�.
			//�ٽ��� �ּҰ��� ��ȯ�ް� ���� �����ϴ� �ڵ带 �ۼ��ϴ°��� �ùٸ� ���̴�.
			ppos = LRemove(&list);
			free(ppos);
		}

		while (LNext(&list, &ppos))
		{
			if (PointComp(ppos, &compPos) == 1)
			{
				ppos = LRemove(&list);
				free(ppos);
			}
		}
	}

	/*** ���� �� ���� ������ ��ü ��� ***/
	printf("���� �������� ��: %d \n", LCount(&list));

	if (LFirst(&list, &ppos))
	{
		ShowPointPos(ppos);

		while (LNext(&list, &ppos))
			ShowPointPos(ppos);
	}
	printf("\n");


	return 0;
}