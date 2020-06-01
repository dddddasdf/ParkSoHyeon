#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include "CLinkedList.h"

int main(void)
{
	// 원형 연결 리스트의 생성 및 초기화 ///////
	List list;
	Staff *StaffTmp;
	int data, i, nodeNum;
	ListInit(&list);
	printf("리스트 초기화\n");

	StaffTmp = (Staff*)malloc(sizeof(Staff));
	SetStaffInformation(StaffTmp, "김철수", 1);
	LInsert(&list, StaffTmp);
	printf("사원 정보 등록\n");

	StaffTmp = (Staff*)malloc(sizeof(Staff));
	SetStaffInformation(StaffTmp, "김영희", 3);
	LInsert(&list, StaffTmp);
	printf("사원 정보 등록\n");

	StaffTmp = (Staff*)malloc(sizeof(Staff));
	SetStaffInformation(StaffTmp, "바둑이", 4);
	LInsert(&list, StaffTmp);
	printf("사원 정보 등록\n");

	StaffTmp = (Staff*)malloc(sizeof(Staff));
	SetStaffInformation(StaffTmp, "김민수", 2);
	LInsert(&list, StaffTmp);
	printf("사원 정보 등록\n");
	puts("");

	InitToday(&list);
	int iSelect = 0;
	char *NameToday = "";
	char *NameTmp = "";
	int iDate = 0;

	while (1)
	{
		NameToday = ReturnName(&list);
		printf("오늘 당직: %s\n", NameToday);
		printf("사용할 메뉴 입력(1. 날짜 지남 / 2. 당직 확인 / 3. 종료)\n입력: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		default:
			printf("없는 메뉴 번호\n");
			break;
		case 1:

			break;
		case 2:
			printf("이름 입력: ");
			printf("날짜 입력: ");
			break;
		case 3:
			break;
		}
	}

	// 리스트에 저장된 데이터를 연속 3회 출력 ///////
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

	// 2의 배수를 찾아서 모두 삭제 ///////
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

	// 전체 데이터 1회 출력 ///////
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