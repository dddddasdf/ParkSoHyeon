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
				printf("���������� �Էµ� ������: %d\n", iTmp);
			break;
		case 3:
			if (LFirst(&list, &iTmp) == FALSE)
				printf("����� ������ ����\n");
			else
			{
				iTmp = LRemove(&list);
				printf("���������� �Էµ� ������ ���� �Ϸ�: %d\n", iTmp);
			}
			break;
		case 4:
			break;
		}
		printf("\n");
	}

	return 0;
}