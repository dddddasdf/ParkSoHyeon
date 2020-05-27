#include "Functions.h"

void AddNewData(LinkedList *List)
{
	int iXTmp = 0, iYTmp = 0;

	std::cout << "X ��ǥ �Է�: ";
	std::cin >> iXTmp;
	std::cout << "Y ��ǥ �Է�: ";
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
		std::cout << "���ϴ� ���� �޴� ����(1. X��ǥ ��ġ�ϴ� �͸�/2. Y��ǥ ��ġ�ϴ� �͸�/3. �� �� ��ġ�ϴ� �͸�)";
		std::cin >> iSelect;

		if (iSelect == 1 || iSelect == 2 || iSelect == 3)
		{
			if (iSelect == 1)
			{
				std::cout << "X��ǥ �Է�: ";
				std::cin >> iXTmp;
			}
			else if (iSelect == 2)
			{
				std::cout << "Y��ǥ �Է�: ";
				std::cin >> iXTmp;
			}
			else
			{
				std::cout << "X��ǥ �Է�: ";
				std::cin >> iXTmp;
				std::cout << "Y��ǥ �Է�: ";
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
			std::cout << "����� �� ��ȣ �Է� ���\n";
	}
}

int main()
{
	int iSelect = 0;

	LinkedList ListOne;
	ListInit(&ListOne);

	while (iSelect != 5)
	{
		std::cout << "���ϴ� �޴� ����(1. ������ �߰� / 2. ������ ���� / 3. ������ ���� / 4. ����)\n";
		std::cout << "�Է�: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		default:
			std::cout << "����� �� ��ȣ �Է� ���\n";
			break;
		case 1:
	/*	{
			int iXTmp = 0, iYTmp = 0;

			std::cout << "X ��ǥ �Է�: ";
			std::cin >> iXTmp;
			std::cout << "Y ��ǥ �Է�: ";
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
		std::cout << "\n";	//�� �̰��ϰ� ���� ���빰 �ʱ�ȭ ��???????????
	}

	DeleteAll(&ListOne);

	return 0;
}