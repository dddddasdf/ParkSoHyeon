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
		printf("현재 데이터의 수: %d \n", LCount(&list));
		printf("메뉴 선택 (1. 데이터 추가 / 2. 데이터 순차 출력 / 3. 데이터 삭제 / 4. 데이터 검색 / 5. 종료\n");
		printf("입력: ");
		scanf("%d", &iSelect);

		switch(iSelect)
		{
		default:
			printf("제대로 된 번호 입력 요망\n");
			break;
		case 1:
		{
			int iX = 0, iY = 0;
			printf("X 입력: ");
			scanf("%d", &iX);
			printf("Y 입력: ");
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
			printf("삭제되길 원하는 좌표의 X값을 입력: ");
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
			printf("검색하고 싶은 좌표의 X값을 입력: ");
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