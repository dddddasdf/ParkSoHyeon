#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"
#include "Point.h"

#define SHUTDOWN 5

int main(void)
{
	List list;
	Point compPos;
	Point * ppos;

	ListInit(&list);

	int iSelect = 0;

	while (iSelect != SHUTDOWN)
	{
		printf("���� �������� ��: %d \n", LCount(&list));
		printf("�޴� ���� (1. ������ �߰� / 2. ������ ���� ��� / 3. ������ ���� / 4. ������ �˻� / 5. ����\n");
		printf("�Է�: ");
		scanf("%d", &iSelect);

		switch(iSelect)
		{
		default:
			printf("����� �� ��ȣ �Է� ���\n");
			break;
		case 1:
		{
			int iX = 0, iY = 0;
			printf("X �Է�: ");
			scanf("%d", &iX);
			printf("Y �Է�: ");
			scanf("%d", &iY);
			ppos = (Point*)malloc(sizeof(Point));
			SetPointPos(ppos, iX, iY);
			LInsert(&list, ppos);
			break;
		}
		case 2:
			if (LFirst(&list, &ppos))
			{
				ShowPointPos(ppos);

				while (LNext(&list, &ppos))
					ShowPointPos(ppos);
			}
			printf("\n");
			break;
		case 3:
		{
			int iX = 0;
			printf("�����Ǳ� ���ϴ� ��ǥ�� X���� �Է�: ");
			scanf("%d", &iX);
			compPos.xpos = iX;
			compPos.ypos = 0;
			if (LFirst(&list, &ppos))
			{
				if (PointComp(ppos, &compPos) == 1 || PointComp(ppos, &compPos) == 0)
				{
					ppos = LRemove(&list);
					free(ppos);
				}

				while (LNext(&list, &ppos))
				{
					if (PointComp(ppos, &compPos) == 1 || PointComp(ppos, &compPos) == 0)
					{
						ppos = LRemove(&list);
						free(ppos);
					}
				}
			}
			break;
		}
		case 4:
		{
			int iX = 0;
			printf("�˻��ϰ� ���� ��ǥ�� X���� �Է�: ");
			scanf("%d", &iX);
			compPos.xpos = iX;
			compPos.ypos = 0;
			if (LFirst(&list, &ppos))
			{
				if (PointComp(ppos, &compPos) == 1 || PointComp(ppos, &compPos) == 0)
					ShowPointPos(ppos);

				while (LNext(&list, &ppos))
				{
					if (PointComp(ppos, &compPos) == 1 || PointComp(ppos, &compPos) == 0)
						ShowPointPos(ppos);
				}
			}
			break;
		}
		case SHUTDOWN:
			break;
		}
		printf("\n");
	}

	return 0;
}