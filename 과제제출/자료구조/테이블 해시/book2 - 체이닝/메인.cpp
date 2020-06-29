#include "Table.h"

int MakeHashNumber(Key KeyTmp)
{
	return ((int)KeyTmp % 100);
}

int MakeCategoryNumber(Key KeyTmp)
{
	return (KeyTmp / 100);
}

int MakeStandard(int NewKey, int Target)
{
	if (NewKey > Target)
		return COMPARE_LARGE;
	if (NewKey == Target)
		return COMPARE_EQUALL;
	else
		return COMPARE_SMALL;
}

int main()
{
	BookTable NewBookList;
	TableInit(&NewBookList, MakeHashNumber, MakeCategoryNumber);

	std::string sBookNameTmp;
	int iKDCTmp = 0;
	std::string sWriterNameTmp;
	int iBookNumberTmp = 0;

	std::string sSearchTmp;
	int iSelect = 0;

	while (1)
	{
		std::cout << "�޴� ����(1. ���� ��� / 2. ���� �˻� / 3. ���� ����)\n";
		std::cout << "�Է�: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		default:
			std::cout << "�ùٸ� ��ȣ �Է� ���\n";
			break;
		case 1:
		{
			Book *BookTmp;
			std::cout << "���� KDC �Է�: ";
			std::cin >> iKDCTmp;
			std::cin.ignore();
			std::cout << "���� �̸� �Է�: ";
			std::getline(std::cin, sBookNameTmp);
			std::cout << "���� ���� �Է�: ";
			std::getline(std::cin, sWriterNameTmp);
			std::cout << "���� ISBN �Է�: ";
			std::cin >> iBookNumberTmp;
			BookTmp = MakeBookData(iBookNumberTmp, iKDCTmp, sBookNameTmp, sWriterNameTmp);

			TableInsert(&NewBookList, iKDCTmp, BookTmp);
		}
		break;
		case 2:
		{
			std::cout << "�˻� �ɼ� ����(1. ���� ��ȣ / 2. KDC / 3. ������ / 4. ���ڸ�)";
			std::cin >> iSelect;

			if (iSelect == 1)	
			{
				std::cout << "���� KDC �Է�: ";
				std::cin >> iBookNumberTmp;

			}
			else if (iSelect == 2)
			{
				std::cout << "���� KDC �Է�: ";
				std::cin >> iBookNumberTmp;

				if (TableIsEmpty(&NewBookList, iBookNumberTmp) == false)
				{
					Book Searching;
					Searching = *TableSearchKDC(&NewBookList, iBookNumberTmp);
					ShowBookData(&Searching);
				}
				else
					std::cout << "�ش��ϴ� ���� ����\n";
			}
			else if (iSelect == 3)
			{
				std::cout << "�˻��� �ܾ� �Է�: ";
				std::cin >> sSearchTmp;

				
			}
			else if (iSelect == 4)
				;
			else
				std::cout << "�ùٸ� ��ȣ �Է� ���\n";
		}
		break;
		case 3:
			std::cout << "���� KDC �Է�: ";
			std::cin >> iBookNumberTmp;
			if (TableIsEmpty(&NewBookList, iBookNumberTmp) == false)
			{
				TableDelete(&NewBookList, iKDCTmp);
				std::cout << "���� �Ϸ�\n";
			}
			else
				std::cout << "�ش��ϴ� ���� ����\n";
			break;
		}
		puts("");

	}
	return 0;
}