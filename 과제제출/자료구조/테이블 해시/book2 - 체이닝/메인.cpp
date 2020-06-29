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
		std::cout << "메뉴 선택(1. 도서 등록 / 2. 도서 검색 / 3. 도서 삭제)\n";
		std::cout << "입력: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		default:
			std::cout << "올바른 번호 입력 요망\n";
			break;
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
			std::cout << "검색 옵션 선택(1. 도서 번호 / 2. KDC / 3. 도서명 / 4. 저자명)";
			std::cin >> iSelect;

			if (iSelect == 1)	
			{
				std::cout << "도서 KDC 입력: ";
				std::cin >> iBookNumberTmp;

			}
			else if (iSelect == 2)
			{
				std::cout << "도서 KDC 입력: ";
				std::cin >> iBookNumberTmp;

				if (TableIsEmpty(&NewBookList, iBookNumberTmp) == false)
				{
					Book Searching;
					Searching = *TableSearchKDC(&NewBookList, iBookNumberTmp);
					ShowBookData(&Searching);
				}
				else
					std::cout << "해당하는 도서 없음\n";
			}
			else if (iSelect == 3)
			{
				std::cout << "검색할 단어 입력: ";
				std::cin >> sSearchTmp;

				
			}
			else if (iSelect == 4)
				;
			else
				std::cout << "올바른 번호 입력 요망\n";
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