#pragma once
#include <iostream>
#include <string>

struct Book
{
	int iBookNumber;
	int iKDC;
	std::string sBookName;
	std::string sBookCatergory;
	std::string sWriter;
};

Book* MakeBookData(int ISBN, int KDC, std::string BookName, std::string Writer);