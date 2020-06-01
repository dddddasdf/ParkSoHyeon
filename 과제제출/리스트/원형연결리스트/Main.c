#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include "CLinkedList.h"

int main(void)
{
	// ���� ���� ����Ʈ�� ���� �� �ʱ�ȭ ///////
	List list;
	Staff *StaffTmp;
	int data, i, nodeNum;
	ListInit(&list);
	printf("����Ʈ �ʱ�ȭ\n");

	StaffTmp = (Staff*)malloc(sizeof(Staff));
	SetStaffInformation(StaffTmp, "��ö��", 1);
	LInsert(&list, StaffTmp);
	printf("��� ���� ���\n");

	StaffTmp = (Staff*)malloc(sizeof(Staff));
	SetStaffInformation(StaffTmp, "�迵��", 3);
	LInsert(&list, StaffTmp);
	printf("��� ���� ���\n");

	StaffTmp = (Staff*)malloc(sizeof(Staff));
	SetStaffInformation(StaffTmp, "�ٵ���", 4);
	LInsert(&list, StaffTmp);
	printf("��� ���� ���\n");

	StaffTmp = (Staff*)malloc(sizeof(Staff));
	SetStaffInformation(StaffTmp, "��μ�", 2);
	LInsert(&list, StaffTmp);
	printf("��� ���� ���\n");
	puts("");

	InitToday(&list);
	int iSelect = 0;
	char *NameToday = "";
	char *NameTmp = "";
	int iDate = 0;

	while (1)
	{
		NameToday = ReturnName(&list);
		printf("���� ����: %s\n", NameToday);
		printf("����� �޴� �Է�(1. ��¥ ���� / 2. ���� Ȯ�� / 3. ����)\n�Է�: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		default:
			printf("���� �޴� ��ȣ\n");
			break;
		case 1:

			break;
		case 2:
			printf("�̸� �Է�: ");
			printf("��¥ �Է�: ");
			break;
		case 3:
			break;
		}
	}

	// ����Ʈ�� ����� �����͸� ���� 3ȸ ��� ///////
	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		for (i = 0; i < LCount(&list) * 3 - 1; i++)
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

		for (i = 0; i < LCount(&list) - 1; i++)
		{
			if (LNext(&list, &data))
				printf("%d ", data);
		}
	}
	system("pause");
	return 0;
}