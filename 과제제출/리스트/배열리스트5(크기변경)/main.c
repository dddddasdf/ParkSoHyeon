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

	printf("1. 등록할 이름 입력: ");
	scanf("%s", NameTmp);
	printf("2. 등록할 연락처 입력: ");
	scanf("%s", PhoneTmp);

	Array[Size - 1] = *MakeNameCard(NameTmp, PhoneTmp);
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
		printf("메뉴 선택(1. 인원 추가 / 2. 정보 검색 / 3. 전화 번호 변경 / 4. 정보 삭제 / 5. 정보 전부 출력 / 6. 종료)\n입력: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		default:
			printf("제대로 된 번호 입력 요망\n");
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