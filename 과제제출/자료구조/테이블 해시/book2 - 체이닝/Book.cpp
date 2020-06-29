#include "Book.h"

Book* MakeBookData(int ISBN, int KDC, std::string BookName, std::string Writer)
{
	Book *NewBook = new Book;

	NewBook->iBookNumber = ISBN;
	NewBook->kKDC = KDC;
	NewBook->sBookName = BookName;
	NewBook->sWriter = Writer;

	int iTmp = KDC / 100;

	switch (iTmp)
	{
	case 0:
		NewBook->sBookCatergory = "총류";
		break;
	case 1:
		NewBook->sBookCatergory = "철학";
		break;
	case 2:
		NewBook->sBookCatergory = "종교";
		break;
	case 3:
		NewBook->sBookCatergory = "사회과학";
		break;
	case 4:
		NewBook->sBookCatergory = "자연과학";
		break;
	case 5:
		NewBook->sBookCatergory = "기술과학";
		break;
	case 6:
		NewBook->sBookCatergory = "예술";
		break;
	case 7:
		NewBook->sBookCatergory = "언어";
		break;
	case 8:
		NewBook->sBookCatergory = "문학";
		break;
	case 9:
		NewBook->sBookCatergory = "역사";
		break;
	}

	return NewBook;
}

void ShowBookData(Book* BookTmp)
{
	std::cout << "도서명: " << BookTmp->sBookName << "\n";
	std::cout << "저자명: " << BookTmp->sWriter << "\n";
	std::cout << "도서 번호: " << BookTmp->iBookNumber << "\n";
	std::cout << "KDC: " << BookTmp->kKDC << "\n";
	std::cout << "분류: " << BookTmp->sBookCatergory << "\n";
}