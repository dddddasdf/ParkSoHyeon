#define _CRT_SECURE_NO_WARNINGS
#include "Table.h"
#include <stdio.h>
#include <stdlib.h>

int MakeHashNumber(Key keyTmp)
{
	return (keyTmp / 100);
}

int main()
{
	Table NewEmployeeList;
	TBLInit(&NewEmployeeList, MakeHashNumber);
	
	char cNameTmp[50];
	int iCitizenNumberTmp = 0;
	char cAddressTmp[50];
	int iSelect = 0;

	while (1)
	{
		printf("�޴� ����(1. ��� ��� / 2. ��� �˻� / 3. ��� ����)\n");
		printf("�Է�: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		case 1:
		{
			Person *PersonTmp;
			printf("��� �ֹ� ��ȣ �Է�: ");
			scanf("%d", &iCitizenNumberTmp);
			printf("��� �ּ� �Է�: ");
			scanf("%s", cAddressTmp);
			printf("��� �̸� �Է�: ");
			scanf("%s", cNameTmp);
			PersonTmp = MakePersonData(iCitizenNumberTmp, cNameTmp, cAddressTmp);

			TBLInsert(&NewEmployeeList, iCitizenNumberTmp, PersonTmp);
		}
			break;
		case 2:
		{
			printf("��� �ֹ� ��ȣ �Է�: ");
			scanf("%d", &iCitizenNumberTmp);
			Person Searching;
			Searching = *TBLSearch(&NewEmployeeList, iCitizenNumberTmp);
			printf("��� �ֹ� ��ȣ: %d, ��� �̸�: %s, ��� �ּ�: %s\n", Searching.ssn, Searching.name, Searching.addr);
		}
			break;
		case 3:
			printf("��� �ֹ� ��ȣ �Է�: ");
			scanf("%d", &iCitizenNumberTmp);
			TBLDelete(&NewEmployeeList, iCitizenNumberTmp);
			printf("���� �Ϸ�\n");
			break;
		}
		puts("");
		
	}


	return 0;
}