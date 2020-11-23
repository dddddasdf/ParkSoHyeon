#include "Person.h"



Person::Person()
{
}

void Person::GetPerson()
{
	std::cout << "나이 입력: ";
	std::cin >> m_iAge;
	std::cout << "이름 입력: ";
	std::cin >> m_sName;
	std::cout << "성별 입력: ";
	std::cin >> m_sGender;
}
void Person::PrintPerson()
{
	std::cout << "나이: " << m_iAge << "\n이름: " << m_sName << "\n성별: " << m_sGender;

}

Person::~Person()
{
}
