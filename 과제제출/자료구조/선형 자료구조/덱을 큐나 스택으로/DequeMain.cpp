#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Deque.h"

#define NOW_STACK 0
#define NOW_QUEUE 1

int main(void)
{
	Deque Stock;
	DequeInit(&Stock);

	int iSelect = 0;
	int iTmp = 0;
	int iIsStyle = NOW_STACK;

	while (1)
	{
		if (iIsStyle == NOW_STACK)
			printf("현재 저장 방식: 스택\n");
		else
			printf("현재 저장 방식: 큐\n");

		printf("메뉴 선택(1. 데이터 입력 / 2. 데이터 삭제 / 3. 데이터 전부 삭제 /4. 저장 방식 전환)\n");
		printf("입력: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		default:
			printf("올바른 번호 입력 요망\n");
			break;
		case 1:
			printf("입력할 데이터 입력: ");
			scanf("%d", &iTmp);
			DQAddLast(&Stock, iTmp);
			break;
		case 2:
			if (DQIsEmpty(&Stock) == TRUE)
				printf("저장 공간 비어있음\n");
			else
			{
				if (iIsStyle == NOW_STACK)
					printf("삭제된 데이터: %d\n", DQRemoveLast(&Stock));
				else
					printf("삭제된 데이터: %d\n", DQRemoveFirst(&Stock));
			}
			break;
		case 3:
			if (DQIsEmpty(&Stock) == TRUE)
				printf("저장 공간 비어있음\n");
			else
			{
				if (iIsStyle == NOW_STACK)
				{
					while (!DQIsEmpty(&Stock))
						printf("%d ", DQRemoveLast(&Stock));
				}
				else
				{
					while (!DQIsEmpty(&Stock))
						printf("%d ", DQRemoveFirst(&Stock));
				}
				puts("");
			}
			break;
		case 4:
			if (DQIsEmpty(&Stock) != TRUE)
			{
				printf("들어 있는 데이터를 비우시겠습니까? 1. 예 2. 아니오\n입력: ");
				scanf("%d", &iSelect);

				if (iSelect == 1)
				{
					if (iIsStyle == NOW_STACK)
					{
						while (!DQIsEmpty(&Stock))
							printf("%d ", DQRemoveLast(&Stock));
					}
					else
					{
						while (!DQIsEmpty(&Stock))
							printf("%d ", DQRemoveFirst(&Stock));
					}
				}
			}
			if (iIsStyle == NOW_STACK)
				iIsStyle = NOW_QUEUE;
			else if (iIsStyle == NOW_QUEUE)
				iIsStyle = NOW_STACK;
			puts("");
			break;
		}

		puts("");
	}


	// Deque의 생성 및 초기화 ///////
	//Deque deq;
	//DequeInit(&deq);

	//// 데이터 넣기 1차 ///////
	//DQAddFirst(&deq, 3);
	//DQAddFirst(&deq, 2);
	//DQAddFirst(&deq, 1);

	//DQAddLast(&deq, 4);
	//DQAddLast(&deq, 5);
	//DQAddLast(&deq, 6);

	//// 데이터 꺼내기 1차 ///////
	//while (!DQIsEmpty(&deq))
	//	printf("%d ", DQRemoveFirst(&deq));

	//printf("\n");

	//// 데이터 넣기 2차 ///////
	//DQAddFirst(&deq, 3);
	//DQAddFirst(&deq, 2);
	//DQAddFirst(&deq, 1);

	//DQAddLast(&deq, 4);
	//DQAddLast(&deq, 5);
	//DQAddLast(&deq, 6);

	//// 데이터 꺼내기 2차 ///////
	//while (!DQIsEmpty(&deq))
	//	printf("%d ", DQRemoveLast(&deq));

	return 0;
}