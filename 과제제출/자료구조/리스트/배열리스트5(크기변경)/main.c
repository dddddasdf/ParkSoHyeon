#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLUS 1
#define MINUS 2


void Resize(NameCard *Array, int Size);

void InputInformation(NameCard *Array, int Size)
{
	char NameTmp[NAME_LEN];
	char PhoneTmp[PHONE_LEN];

	printf("1. ����� �̸� �Է�: ");
	scanf("%s", NameTmp);
	printf("2. ����� ����ó �Է�: ");
	scanf("%s", PhoneTmp);

	Array[Size - 1] = *MakeNameCard(NameTmp, PhoneTmp);
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

void Resize(NameCard *Array, int Size)
{
	Array = (NameCard*)realloc(Array, sizeof(NameCard) * Size);
	strcpy(Array[Size - 1].name, "");
	strcpy(Array[Size - 1].phone, "");
}

int main()
{
	int iSize = 0;
	int iSelect = 0;

	NameCard *CardArray = (NameCard*)malloc(sizeof(NameCard) * iSize);

	while (iSelect != 6)
	{
		printf("�޴� ����(1. �ο� �߰� / 2. ���� �˻� / 3. ��ȭ ��ȣ ���� / 4. ���� ���� / 5. ���� ���� ��� / 6. ����)\n�Է�: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		default:
			printf("����� �� ��ȣ �Է� ���\n");
			break;
		case 1:
			iSize++;
			CardArray = (NameCard*)realloc(CardArray, sizeof(NameCard) * iSize);
			strcpy(CardArray[iSize - 1].name, "");
			strcpy(CardArray[iSize - 1].phone, "");
			InputInformation(CardArray, iSize);
			break;
		case 2:
			SearchInformation(CardArray, iSize);
			break;
		case 3:
			SearchPhoneNumber(CardArray, iSize);
			break;
		case 4:
			DeleteInformation(CardArray, &iSize);
			CardArray = (NameCard*)realloc(CardArray, sizeof(NameCard) * iSize);
			break;
		case 5:
			ShowLinear(CardArray, iSize);
			break;
		case 6:
			free(CardArray);
			break;
		}
		printf("\n");
	}

	return 0;
}