#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "CLinkedList.h"

int main(void)
{
	// ���� ���� ����Ʈ�� ���� �� �ʱ�ȭ ///////
	List list;
	int data, i, nodeNum;
	ListInit(&list);


	int iSelect = 0;
	int iTmp = 0;

	while (iSelect != 4)
	{
		printf("�޴� ����(1. ������ �Է� / 2. ���� ���������� �Է��� ������ Ȯ�� / 3. ���� ���������� �Է��� ������ ���� / 4. ����\n�Է�: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		default:
			printf("�ùٸ� ��ȣ �Է� ���\n");
			break;
		case 1:
			printf("���� �Է�: ");
			scanf("%d", &iTmp);
			LInsertFront(&list, iTmp);
			break;
		case 2:
			if (LFirst(&list, &iTmp) == FALSE)
				printf("����� ������ ����\n");
			else
			{

			}
			break;
		case 3:
			break;
		case 4:
			break;
		}
	}

	// ����Ʈ�� 5���� �����͸� ���� /////// 
	LInsert(&list, 3);
	LInsert(&list, 4);
	LInsert(&list, 5);
	LInsertFront(&list, 2);
	LInsertFront(&list, 1);

	// ����Ʈ�� ����� �����͸� ���� 3ȸ ��� ///////
	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		for (i = 0; i<LCount(&list) * 3 - 1; i++)
		{
			if (LNext(&list, &data))
				printf("%d ", data);
		}
	}
	printf("\n");

	// 2�� ����� ã�Ƽ� ��� ���� ///////
	nodeNum = LCount(&list);

	if (nodeNum != 0)
	{
		LFirst(&list, &data);
		if (data % 2 == 0)
			LRemove(&list);

		for (i = 0; i < nodeNum - 1; i++)
		{
			LNext(&list, &data);
			if (data % 2 == 0)
				LRemove(&list);
		}
	}

	// ��ü ������ 1ȸ ��� ///////
	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		for (i = 0; i<LCount(&list) - 1; i++)
		{
			if (LNext(&list, &data))
				printf("%d ", data);
		}
	}
	system("pause");
	return 0;
}