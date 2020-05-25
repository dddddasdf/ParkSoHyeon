#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InputInformation(NameCard *Array, int Size)
{
	char NameTmp[NAME_LEN];
	char PhoneTmp[PHONE_LEN];

	printf("1. 등록할 이름 입력: ");
	scanf("%s", NameTmp);
	printf("2. 등록할 연락처 입력: ");
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
	printf("검색할 이름 입력: ");
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
	printf("해당하는 이름을 가진 사람이 없습니다.\n");
}

void SearchPhoneNumber(NameCard *Array, int Size)
{
	printf("검색할 이름 입력: ");
	char NameSearch[NAME_LEN];
	scanf("%s", NameSearch);

	for (int i = 0; i < Size; i++)
	{
		if (NameCompare(&Array[i], NameSearch) == 0)
		{
			char PhoneNumberTmp[PHONE_LEN];
			printf("변경할 전화번호를 입력: ");
			scanf("%s", PhoneNumberTmp);
			ChangePhoneNum(&Array[i], PhoneNumberTmp);
			return;
		}
	}
	printf("해당하는 이름을 가진 사람이 없습니다.\n");
}

void DeleteInformation(NameCard *Array, int *Size)
{
	printf("검색할 이름 입력: ");
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
	printf("해당하는 이름을 가진 사람이 없습니다.\n");
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
	printf("등록할 인원수 입력: ");
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