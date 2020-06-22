#include "BinarySearchTree.h"

int main()
{
	BTreeNode *NewRootNode;
	BSTMakeAndInit(&NewRootNode);

	int iSelect = 0, iTmp = 0;
	while (1)
	{
		printf("메뉴 선택(1. 데이터 입력 2. 입력된 데이터들 출력)\n");
		printf("입력: ");
		scanf_s("%d", &iSelect, sizeof(iSelect));
		switch (iSelect)
		{
		default:
			printf("올바른 메뉴 번호 입력\n");
			break;
		case 1:
			printf("입력할 데이터 입력: \n");
			scanf_s("%d", &iTmp, sizeof(iTmp));
			BSTInsert(&NewRootNode, iTmp);
			break;
		case 2:
			break;
		}
		puts("");
	}

	return 0;
}