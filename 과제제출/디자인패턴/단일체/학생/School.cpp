#include "School.h"



School::School()
{
}

void School::GetSchool()
{
	std::cout << "�г� �Է�: ";
	std::cin >> m_iGrade;
	std::cout << "�� �Է�: ";
	std::cin >> m_iClass;
	std::cout << "�л� ��ȣ �Է�: ";
	std::cin >> m_iNumber;
}

void School::PrintSchool()
{
	std::cout << m_iGrade << "�г� " << m_iClass << "�� " << m_iNumber << "�� �л�\n";
}

School::~School()
{
}
