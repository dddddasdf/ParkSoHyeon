#include "BinarySearchTree.h"

int main()
{
	BTreeNode NewRootNode;
	NewRootNode = *MakeBTreeNode();

	int iSelect = 0;
	while (1)
	{
		printf("�޴� ����(1. ������ �Է�)\n");
		printf("�Է�: ");
		scanf_s("%d", &iSelect, sizeof(iSelect));
		switch (iSelect)
		{
		default:
			printf("�ùٸ� �޴� ��ȣ �Է�\n");
			break;
		case 1:
		}
		puts("");
	}

	return 0;
}