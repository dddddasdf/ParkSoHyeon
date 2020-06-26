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
		std::cout << "메뉴 선택(1. 도서 등록 / 2. 도서 검색 / 3. 도서 삭제)\n";
		std::cout << "입력: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		case 1:
		{
			Book *BookTmp;
			std::cout << "도서 KDC 입력: ";
			std::cin >> iKDCTmp;
			std::cin.ignore();
			std::cout << "도서 이름 입력: ";
			std::getline(std::cin, sBookNameTmp);
			std::cout << "도서 저자 입력: ";
			std::getline(std::cin, sWriterNameTmp);
			std::cout << "도서 ISBN 입력: ";
			std::cin >> iBookNumberTmp;
			BookTmp = MakeBookData(iBookNumberTmp, iKDCTmp, sBookNameTmp, sWriterNameTmp);

			TableInsert(&NewBookList, iKDCTmp, BookTmp);
		}
		break;
		case 2:
		{
			std::cout << "도서 KDC 입력: ";
			std::cin >> iBookNumberTmp;
			if (TableIsEmpty(&NewBookList, iBookNumberTmp) == false)
			{
				Book Searching;
				Searching = *TableSearch(&NewBookList, iBookNumberTmp);
				std::cout << "도서 KDC: " << Searching.iKDC << ", 도서 이름: " << Searching.sBookName << ", 도서 저자: " << Searching.sWriter << ", 도서 분류: " << Searching.sBookCatergory <<
					", 도서 ISBN: " << Searching.iBookNumber << "\n";
			}
			else
				std::cout << "해당하는 도서 없음\n";
		}
		break;
		case 3:
			std::cout << "도서 KDC 입력: ";
			std::cin >> iBookNumberTmp;
			if (TableIsEmpty(&NewBookList, iBookNumberTmp) == false)
			{
				TableDelete(&NewBookList, iKDCTmp);
				std::cout << "삭제 완료\n";
			}
			else
				std::cout << "해당하는 도서 없음\n";
			break;
		}
		puts("");

	}
	return 0;
}