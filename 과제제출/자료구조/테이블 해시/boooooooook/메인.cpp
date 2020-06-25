#include "Table.h"

int MakeHashNumber(Key KeyTmp)
{
	return (KeyTmp % 100);
}

int MakeCategoryNumber(Key KeyTmp)
{
	return (KeyTmp / 100);
}

int main()
{
	BookTable NewBookList;
	TableInit(&NewBookList, MakeHashNumber, MakeCategoryNumber);

	std::string sBookNameTmp;
	int iKDCTmp = 0;
	std::string sWriterNameTmp;
	int iBookNumberTmp = 0;
	int iSelect = 0;

	while (1)
	{
		std::cout << "�޴� ����(1. ���� ��� / 2. ���� �˻� / 3. ���� ����)\n";
		std::cout << "�Է�: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		case 1:
		{
			Book *BookTmp;
			std::cout << "���� KDC �Է�: ";
			std::cin >> iKDCTmp;
			std::cout << "���� �̸� �Է�: ";
			std::cin >> sBookNameTmp;
			std::cout << "���� ���� �Է�: ";
			std::cin >> sWriterNameTmp;
			std::cout << "���� ISBN �Է�: ";
			std::cin >> iBookNumberTmp;
			BookTmp = MakeBookData(iBookNumberTmp, iKDCTmp, sBookNameTmp, sWriterNameTmp);

			TableInsert(&NewBookList, iKDCTmp, BookTmp);
		}
		break;
		case 2:
		{
			std::cout << "���� KDC �Է�: ";
			std::cin >> iBookNumberTmp;
			Book Searching;
			Searching = *TableSearch(&NewBookList, iBookNumberTmp);
			if (Searching.iBookNumber != NULL)
				std::cout << "���� KDC: " << Searching.iKDC << ", ���� �̸�: " << Searching.sBookName << ", ���� ����: " << Searching.sWriter << ", ���� �з�: " << Searching.sBookCatergory <<
				", ���� ISBN: " << Searching.iBookNumber << "\n";
			else
				std::cout << "�ش��ϴ� ���� ����\n";
		}
		break;
		case 3:
			std::cout << "���� KDC �Է�: ";
			std::cin >> iBookNumberTmp;
			TableDelete(&NewBookList, iKDCTmp);
			printf("���� �Ϸ�\n");
			break;
		}
		puts("");

	}
	return 0;
}