#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Deque.h"

int main(void)
{
	Deque Queue;
	DequeInit(&Queue);

	int iSelect = 0;
	int iTmp = 0;

	while (1)
	{
		printf("메뉴 선택(1. 데이터 입력 / 3. 데이터 삭제)\n");
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
			DQAddLast(&Queue, iTmp);
			break;
		case 3:
			if (DQIsEmpty(&Queue) == TRUE)
				printf("큐 비어있음\n");
			else
				printf("삭제된 데이터: %d\n", DQRemoveFirst(&Queue));
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