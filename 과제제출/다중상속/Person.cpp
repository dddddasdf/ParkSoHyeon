#include "Person.h"



Person::Person()
{
}

void Person::GetPerson()
{
	std::cout << "���� �Է�: ";
	std::cin >> m_iAge;
	std::cout << "�̸� �Է�: ";
	std::cin >> m_sName;
	std::cout << "���� �Է�: ";
	std::cin >> m_sGender;
}
void Person::PrintPerson()
{
	std::cout << "����: " << m_iAge << "\n�̸�: " << m_sName << "\n����: " << m_sGender;

}

Person::~Person()
{
}
