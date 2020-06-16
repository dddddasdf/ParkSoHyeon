#include "PriorityQueue.h"

int CompareStringLength(std::string String1, std::string String2)
{
	int iStringLength1 = String1.length();
	int iStringLength2 = String2.length();

	return (iStringLength2 - iStringLength1);
}

int main()
{
	Heap NewHeap;
	PriorityQueueInit(&NewHeap, CompareStringLength);

	int iSelect = 0;
	std::string sTmp;

	while (iSelect != 3)
	{
		std::cout << "�޴��� ����(1. ������ ���� / 2. ������ ��� / 3. ����)\n";
		std::cout << "�Է�: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		case 1:
			std::cout << "�Է��� ���ڿ� �Է�: ";
			std::cin >> sTmp;
			EnqueuePriorityQueue(&NewHeap, sTmp);
			std::cout << "�Է� ����\n";
			break;
		case 2:
			if (IsQueueEmpty(&NewHeap) == true)
				std::cout << "ť �������\n";
			else
			{
				std::cout << DequeuePriorityQueue(&NewHeap);
				std::cout << "\n";
			}
			break;
		case 3:
			break;
		}
		std::cout << "\n";
	}

	return 0;
}