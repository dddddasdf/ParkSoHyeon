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
		std::cout << "메뉴를 선택(1. 데이터 삽입 / 2. 데이터 출력 / 3. 종료)\n";
		std::cout << "입력: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		case 1:
			std::cout << "입력할 문자열 입력: ";
			std::cin >> sTmp;
			EnqueuePriorityQueue(&NewHeap, sTmp);
			std::cout << "입력 성공\n";
			break;
		case 2:
			if (IsQueueEmpty(&NewHeap) == true)
				std::cout << "큐 비어있음\n";
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