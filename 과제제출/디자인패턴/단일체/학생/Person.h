#pragma once
#include "Headers.h"

class Person
{
private:
	int m_iAge;
	std::string m_sName;
	std::string m_sGender;
public:
	Person();
	void GetPerson();
	void PrintPerson();
	~Person();
};

