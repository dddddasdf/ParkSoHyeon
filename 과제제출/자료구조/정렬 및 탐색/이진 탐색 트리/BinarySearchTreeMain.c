#include "BinarySearchTree.h"

int main()
{
	BTreeNode *NewRootNode;
	BSTMakeAndInit(&NewRootNode);

	int iSelect = 0, iTmp = 0;
	while (1)
	{
		printf("�޴� ����(1. ������ �Է� 2. �Էµ� �����͵� ���)\n");
		printf("�Է�: ");
		scanf_s("%d", &iSelect, sizeof(iSelect));
		switch (iSelect)
		{
		default:
			printf("�ùٸ� �޴� ��ȣ �Է�\n");
			break;
		case 1:
			printf("�Է��� ������ �Է�: \n");
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