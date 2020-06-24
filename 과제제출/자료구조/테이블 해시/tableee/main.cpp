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
		printf("메뉴 선택(1. 사원 등록 / 2. 사원 검색 / 3. 사원 삭제)\n");
		printf("입력: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		case 1:
		{
			Person *PersonTmp;
			printf("사원 주민 번호 입력: ");
			scanf("%d", &iCitizenNumberTmp);
			printf("사원 주소 입력: ");
			scanf("%s", cAddressTmp);
			printf("사원 이름 입력: ");
			scanf("%s", cNameTmp);
			PersonTmp = MakePersonData(iCitizenNumberTmp, cNameTmp, cAddressTmp);

			TBLInsert(&NewEmployeeList, iCitizenNumberTmp, PersonTmp);
		}
			break;
		case 2:
		{
			printf("사원 주민 번호 입력: ");
			scanf("%d", &iCitizenNumberTmp);
			Person Searching;
			Searching = *TBLSearch(&NewEmployeeList, iCitizenNumberTmp);
			printf("사원 주민 번호: %d, 사원 이름: %s, 사원 주소: %s\n", Searching.ssn, Searching.name, Searching.addr);
		}
			break;
		case 3:
			printf("사원 주민 번호 입력: ");
			scanf("%d", &iCitizenNumberTmp);
			TBLDelete(&NewEmployeeList, iCitizenNumberTmp);
			printf("삭제 완료\n");
			break;
		}
		puts("");
		
	}


	return 0;
}