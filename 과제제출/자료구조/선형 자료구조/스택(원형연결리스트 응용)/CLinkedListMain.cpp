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
				printf("마지막으로 입력된 데이터: %d\n", iTmp);
			break;
		case 3:
			if (LFirst(&list, &iTmp) == FALSE)
				printf("저장된 데이터 없음\n");
			else
			{
				iTmp = LRemove(&list);
				printf("마지막으로 입력된 데이터 제거 완료: %d\n", iTmp);
			}
			break;
		case 4:
			break;
		}
		printf("\n");
	}

	return 0;
}