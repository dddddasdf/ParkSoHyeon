#include "BinarySearchTree.h"

int main()
{
	BTreeNode NewRootNode;
	NewRootNode = *MakeBTreeNode();

	int iSelect = 0;
	while (1)
	{
		printf("메뉴 선택(1. 데이터 입력)\n");
		printf("입력: ");
		scanf_s("%d", &iSelect, sizeof(iSelect));
		switch (iSelect)
		{
		default:
			printf("올바른 메뉴 번호 입력\n");
			break;
		case 1:
		}
		puts("");
	}

	return 0;
}