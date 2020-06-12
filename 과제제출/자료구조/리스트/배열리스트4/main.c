#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InputInformation(NameCard *Array, int Size)
{
	char NameTmp[NAME_LEN];
	char PhoneTmp[PHONE_LEN];

	printf("1. ����� �̸� �Է�: ");
	scanf("%s", NameTmp);
	printf("2. ����� ����ó �Է�: ");
	scanf("%s", PhoneTmp);

	for (int i = 0; i < Size; i++)
	{
		if (strcmp(Array[i].name, "") == 0)
		{
			Array[i] = *MakeNameCard(NameTmp, PhoneTmp);
			break;
		}
	}
}

void SearchInformation(NameCard *Array, int Size)
{
	printf("�˻��� �̸� �Է�: ");
	char NameSearch[NAME_LEN];
	scanf("%s", NameSearch);

	for (int i = 0; i < Size; i++)
	{
		if (NameCompare(&Array[i], NameSearch) == 0)
		{
			ShowNameCardInfo(&Array[i]);
			return;
		}
	}
	printf("�ش��ϴ� �̸��� ���� ����� �����ϴ�.\n");
}

void SearchPhoneNumber(NameCard *Array, int Size)
{
	printf("�˻��� �̸� �Է�: ");
	char NameSearch[NAME_LEN];
	scanf("%s", NameSearch);

	for (int i = 0; i < Size; i++)
	{
		if (NameCompare(&Array[i], NameSearch) == 0)
		{
			char PhoneNumberTmp[PHONE_LEN];
			printf("������ ��ȭ��ȣ�� �Է�: ");
			scanf("%s", PhoneNumberTmp);
			ChangePhoneNum(&Array[i], PhoneNumberTmp);
			return;
		}
	}
	printf("�ش��ϴ� �̸��� ���� ����� �����ϴ�.\n");
}

void DeleteInformation(NameCard *Array, int *Size)
{
	printf("�˻��� �̸� �Է�: ");
	char NameSearch[NAME_LEN];
	scanf("%s", NameSearch);

	for (int i = 0; i < *Size; i++)
	{
		if (NameCompare(&Array[i], NameSearch) == 0)
		{
			for (int j = i; j < *Size; j++)
			{
				if (j + 1 == *Size)
				{
					strcpy(Array[j].name, "");
					strcpy(Array[j].phone, "");
					(*Size)--;
					return;
				}
				else
					Array[j] = Array[j + 1];
			}
		}
	}
	printf("�ش��ϴ� �̸��� ���� ����� �����ϴ�.\n");
}

void ShowLinear(NameCard *Array, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		if (&Array[i] != 0)
			ShowNameCardInfo(&Array[i]);
	}
}

int main()
{
	int iSize = 0;
	printf("����� �ο��� �Է�: ");
	scanf("%d", &iSize);
	
	NameCard *CardArray = (NameCard*)calloc(iSize, sizeof(NameCard));

	int iNumberOfInput = 0;

	while (iNumberOfInput != iSize)
	{
		InputInformation(CardArray, iSize);
		iNumberOfInput++;
	}

	SearchInformation(CardArray, iSize);
	SearchPhoneNumber(CardArray, iSize);
	DeleteInformation(CardArray, &iSize);
	ShowLinear(CardArray, iSize);

	free(CardArray);

	return 0;
}