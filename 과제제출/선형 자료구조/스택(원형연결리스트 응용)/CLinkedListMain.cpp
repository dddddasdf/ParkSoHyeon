#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "CLinkedList.h"

int main(void)
{
	// 원형 연결 리스트의 생성 및 초기화 ///////
	List list;
	int data, i, nodeNum;
	ListInit(&list);


	int iSelect = 0;
	int iTmp = 0;

	while (iSelect != 4)
	{
		printf("메뉴 선택(1. 데이터 입력 / 2. 가장 마지막으로 입력한 데이터 확인 / 3. 가장 마지막으로 입력한 데이터 제거 / 4. 종료\n입력: ");
		scanf("%d", &iSelect);

		switch (iSelect)
		{
		default:
			printf("올바른 번호 입력 요망\n");
			break;
		case 1:
			printf("숫자 입력: ");
			scanf("%d", &iTmp);
			LInsertFront(&list, iTmp);
			break;
		case 2:
			if (LFirst(&list, &iTmp) == FALSE)
				printf("저장된 데이터 없음\n");
			else
			{

			}
			break;
		case 3:
			break;
		case 4:
			break;
		}
	}

	// 리스트에 5개의 데이터를 저장 /////// 
	LInsert(&list, 3);
	LInsert(&list, 4);
	LInsert(&list, 5);
	LInsertFront(&list, 2);
	LInsertFront(&list, 1);

	// 리스트에 저장된 데이터를 연속 3회 출력 ///////
	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		for (i = 0; i<LCount(&list) * 3 - 1; i++)
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

		for (i = 0; i<LCount(&list) - 1; i++)
		{
			if (LNext(&list, &data))
				printf("%d ", data);
		}
	}
	system("pause");
	return 0;
}