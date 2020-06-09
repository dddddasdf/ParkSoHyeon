#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdbool.h>
#include "CLinkedList.h"

int main(void)
{
	// 원형 연결 리스트의 생성 및 초기화 ///////
	List list;
	Staff *StaffTmp;
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
	char NameTmp[50];
	int iDate = 0;

	while (iSelect != 3)
	{
		NameToday = ReturnName(&list, 1);
		printf("오늘 당직: %s\n", NameToday);
		printf("사용할 메뉴 입력(1. 날짜 지남 / 2. 당직 확인 / 3. 종료)\n입력: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		default:
			printf("없는 메뉴 번호\n");
			break;
		case 1:
			MoveNextDay(&list);
			break;
		case 2:
			printf("이름 입력: ");
			scanf("%s", NameTmp);
			printf("날짜 입력: ");
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
					printf("일치하는 사원 없음\n");
				else
				{
					CheckStaff(&list, iDate);
					printf("%d일 후 당직 예정 사원\n: ", iDate);
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