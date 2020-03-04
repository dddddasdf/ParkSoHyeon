#include "School.h"



School::School()
{
}

void School::GetSchool()
{
	std::cout << "학년 입력: ";
	std::cin >> m_iGrade;
	std::cout << "반 입력: ";
	std::cin >> m_iClass;
	std::cout << "학생 번호 입력: ";
	std::cin >> m_iNumber;
}

void School::PrintSchool()
{
	std::cout << m_iGrade << "학년 " << m_iClass << "반 " << m_iNumber << "번 학생\n";
}

School::~School()
{
}
