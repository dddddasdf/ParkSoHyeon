#include "Book.h"

Book* MakeBookData(int ISBN, int KDC, std::string BookName, std::string Writer)
{
	Book *NewBook = new Book;

	NewBook->iBookNumber = ISBN;
	NewBook->iKDC = KDC;
	NewBook->sBookName = BookName;
	NewBook->sWriter = Writer;

	int iTmp = KDC / 100;

	switch (iTmp)
	{
	case 0:
		NewBook->sBookCatergory = "�ѷ�";
		break;
	case 1:
		NewBook->sBookCatergory = "ö��";
		break;
	case 2:
		NewBook->sBookCatergory = "����";
		break;
	case 3:
		NewBook->sBookCatergory = "��ȸ����";
		break;
	case 4:
		NewBook->sBookCatergory = "�ڿ�����";
		break;
	case 5:
		NewBook->sBookCatergory = "�������";
		break;
	case 6:
		NewBook->sBookCatergory = "����";
		break;
	case 7:
		NewBook->sBookCatergory = "���";
		break;
	case 8:
		NewBook->sBookCatergory = "����";
		break;
	case 9:
		NewBook->sBookCatergory = "����";
		break;
	}
}