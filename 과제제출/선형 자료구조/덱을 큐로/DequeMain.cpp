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
		printf("�޴� ����(1. ������ �Է� / 3. ������ ����)\n");
		printf("�Է�: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		default:
			printf("�ùٸ� ��ȣ �Է� ���\n");
			break;
		case 1:
			printf("�Է��� ������ �Է�: ");
			scanf("%d", &iTmp);
			DQAddLast(&Queue, iTmp);
			break;
		case 3:
			if (DQIsEmpty(&Queue) == TRUE)
				printf("ť �������\n");
			else
				printf("������ ������: %d\n", DQRemoveFirst(&Queue));
			break;
		}

		puts("");
	}


	// Deque�� ���� �� �ʱ�ȭ ///////
	//Deque deq;
	//DequeInit(&deq);

	//// ������ �ֱ� 1�� ///////
	//DQAddFirst(&deq, 3);
	//DQAddFirst(&deq, 2);
	//DQAddFirst(&deq, 1);

	//DQAddLast(&deq, 4);
	//DQAddLast(&deq, 5);
	//DQAddLast(&deq, 6);

	//// ������ ������ 1�� ///////
	//while (!DQIsEmpty(&deq))
	//	printf("%d ", DQRemoveFirst(&deq));

	//printf("\n");

	//// ������ �ֱ� 2�� ///////
	//DQAddFirst(&deq, 3);
	//DQAddFirst(&deq, 2);
	//DQAddFirst(&deq, 1);

	//DQAddLast(&deq, 4);
	//DQAddLast(&deq, 5);
	//DQAddLast(&deq, 6);

	//// ������ ������ 2�� ///////
	//while (!DQIsEmpty(&deq))
	//	printf("%d ", DQRemoveLast(&deq));

	return 0;
}