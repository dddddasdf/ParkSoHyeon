#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>

void InputInformation(int Array[])
{
	char NameTmp[NAME_LEN];
	char PhoneTmp[PHONE_LEN];

	printf("1. 등록할 이름 입력: ");
	scanf("%s", NameTmp);
	printf("2. 등록할 연락처 입력: ");
	scanf("%s", PhoneTmp);

	for (int i = 0; i < 3; i++)
	{
		if (Array[i] == 0)
		{
			Array[i] = MakeNameCard(NameTmp, PhoneTmp);
			break;
		}
	}
}

void SearchInformation()
{

}

void SearchPhoneNumber()
{

}

void DeleteInformation()
{

}

int main()
{
	int CardArray[3] = { 0 };	//배열 리스트 생성

	InputInformation(CardArray);
	InputInformation(CardArray);
	InputInformation(CardArray);


	return 0;
}