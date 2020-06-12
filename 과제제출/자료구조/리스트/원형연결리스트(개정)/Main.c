#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdbool.h>
#include "CLinkedList.h"

int main(void)
{
	// ���� ���� ����Ʈ�� ���� �� �ʱ�ȭ ///////
	List list;
	Staff *StaffTmp;
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
	char NameTmp[50];
	int iDate = 0;

	while (iSelect != 3)
	{
		NameToday = ReturnName(&list, 1);
		printf("���� ����: %s\n", NameToday);
		printf("����� �޴� �Է�(1. ��¥ ���� / 2. ���� Ȯ�� / 3. ����)\n�Է�: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		default:
			printf("���� �޴� ��ȣ\n");
			break;
		case 1:
			MoveNextDay(&list);
			break;
		case 2:
			printf("�̸� �Է�: ");
			scanf("%s", NameTmp);
			printf("��¥ �Է�: ");
			scanf("%d", &iDate);
			{
				LFirst(&list, &StaffTmp);
				int bIsCorrect = FALSE;

				if (strcmp(StaffTmp->sName, NameTmp) == 0)
					bIsCorrect = TRUE;
				else
				{
					for (int i = 1; i < list.NumberOfData; i++)
					{
						LNext(&list, &StaffTmp);

						if (strcmp(StaffTmp->sName, NameTmp) == 0)
						{
							bIsCorrect = TRUE;
							break;
						}
					}
				}
				
				if (bIsCorrect == FALSE)
					printf("��ġ�ϴ� ��� ����\n");
				else
				{
					CheckStaff(&list, iDate);
					printf("%d�� �� ���� ���� ���\n: ", iDate);
					ShowStaffInformation(list.Current->data);
				}
			}
			break;
		case 3:
			break;
		}
		printf("\n");
	}
	
	return 0;
}