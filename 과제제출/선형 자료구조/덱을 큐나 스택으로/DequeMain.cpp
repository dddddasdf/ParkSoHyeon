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
			printf("���� ���� ���: ����\n");
		else
			printf("���� ���� ���: ť\n");

		printf("�޴� ����(1. ������ �Է� / 2. ������ ���� / 3. ������ ���� ���� /4. ���� ��� ��ȯ)\n");
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
			DQAddLast(&Stock, iTmp);
			break;
		case 2:
			if (DQIsEmpty(&Stock) == TRUE)
				printf("���� ���� �������\n");
			else
			{
				if (iIsStyle == NOW_STACK)
					printf("������ ������: %d\n", DQRemoveLast(&Stock));
				else
					printf("������ ������: %d\n", DQRemoveFirst(&Stock));
			}
			break;
		case 3:
			if (DQIsEmpty(&Stock) == TRUE)
				printf("���� ���� �������\n");
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
				printf("��� �ִ� �����͸� ���ðڽ��ϱ�? 1. �� 2. �ƴϿ�\n�Է�: ");
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