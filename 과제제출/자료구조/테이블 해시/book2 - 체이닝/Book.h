#pragma once
#include <iostream>
#include <string>

typedef double KDC;

struct Book
{
	int iBookNumber;
	KDC kKDC;
	std::string sBookName;
	std::string sBookCatergory;
	std::string sWriter;
};

Book* MakeBookData(int ISBN, int KDC, std::string BookName, std::string Writer);

void ShowBookData(Book* BookTmp);