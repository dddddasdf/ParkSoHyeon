#include "Functions.h"

void AddNewData(LinkedList *List)
{
	int iXTmp = 0, iYTmp = 0;

	std::cout << "X 좌표 입력: ";
	std::cin >> iXTmp;
	std::cout << "Y 좌표 입력: ";
	std::cin >> iYTmp;

	Point NewPoint;

	SetPointCoordinate(&NewPoint, iXTmp, iYTmp);

	NodeInsert(List, &NewPoint);
}

void ShowLinear(LinkedList *List)
{
	Point TmpPoint;

	if (ListFirst(List, &TmpPoint) != false)
	{
		ShowCoordinate(&TmpPoint);

		while (ListNext(List, &TmpPoint))
			ShowCoordinate(&TmpPoint);
	}
}

void DeleteData(LinkedList *List)
{
	int iSelect = 0;
	int iXTmp = 0, iYTmp = 0;
	Point TmpPoint;
	Point TargetPoint;
	TmpPoint.XPosition = 0;
	TmpPoint.YPosition = 0;
	TargetPoint.XPosition = 0;
	TargetPoint.YPosition = 0;

	while (1)
	{
		std::cout << "원하는 삭제 메뉴 선택(1. X좌표 일치하는 것만/2. Y좌표 일치하는 것만/3. 둘 다 일치하는 것만)";
		std::cin >> iSelect;

		if (iSelect == 1 || iSelect == 2 || iSelect == 3)
		{
			if (iSelect == 1)
			{
				std::cout << "X좌표 입력: ";
				std::cin >> iXTmp;
			}
			else if (iSelect == 2)
			{
				std::cout << "Y좌표 입력: ";
				std::cin >> iXTmp;
			}
			else
			{
				std::cout << "X좌표 입력: ";
				std::cin >> iXTmp;
				std::cout << "Y좌표 입력: ";
				std::cin >> iXTmp;
			}

			SetPointCoordinate(&TargetPoint, iXTmp, iYTmp);

			if (ListFirst(List, &TmpPoint) != false)
			{
				if (ComparePoints(&TmpPoint, &TargetPoint) == iSelect)
					DeleteNode(List);

				while (ListNext(List, &TmpPoint))
				{
					if (ComparePoints(&TmpPoint, &TargetPoint) == iSelect)
						DeleteNode(List);
				}
			}

			return;
		}
		else
			std::cout << "제대로 된 번호 입력 요망\n";
	}
}

int main()
{
	int iSelect = 0;

	LinkedList ListOne;
	ListInit(&ListOne);

	while (iSelect != 5)
	{
		std::cout << "원하는 메뉴 선택(1. 데이터 추가 / 2. 데이터 열람 / 3. 데이터 삭제 / 4. 종료)\n";
		std::cout << "입력: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		default:
			std::cout << "제대로 된 번호 입력 요망\n";
			break;
		case 1:
	/*	{
			int iXTmp = 0, iYTmp = 0;

			std::cout << "X 좌표 입력: ";
			std::cin >> iXTmp;
			std::cout << "Y 좌표 입력: ";
			std::cin >> iYTmp;

			Point NewPoint;

			SetPointCoordinate(&NewPoint, iXTmp, iYTmp);

			NodeInsert(ListOne, &NewPoint);
		}*/
			break;
		case 2:
			ShowLinear(&ListOne);
			break;
		case 3:
			DeleteData(&ListOne);
			break;
		case 5:
			break;
		}
		std::cout << "\n";	//왜 이거하고 나면 내용물 초기화 됨???????????
	}

	DeleteAll(&ListOne);

	return 0;
}