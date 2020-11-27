#include "Student.h"
#include <string>

Student::Student()
{
	std::cout << "�л� �̸� �Է�: ";
	std::cin >> m_sStudentName;
	std::cout << "�л� �г� �Է�: ";
	std::cin >> m_iGrade;
	std::cout << "�л� ��ȣ �Է�: ";
	std::cin >> m_iStudentNumber;
	std::cout << "���� ���� �Է�: ";
	std::cin >> m_iKoreanScore;
	std::cout << "���� ���� �Է�: ";
	std::cin >> m_iMathScore;
	std::cout << "���� ���� �Է�: ";
	std::cin >> m_iEnglishScore;
}

int Student::ReturnValue(int StudentInfoType)
{
	switch (StudentInfoType)
	{
	case INFO_GRADE:
		return m_iGrade;
	case INFO_NUMBER:
		return m_iStudentNumber;
	case INFO_KOREANSCORE:
		return m_iKoreanScore;
	case INFO_MATHSCORE:
		return m_iMathScore;
	case INFO_ENGLISHSCORE:
		return m_iEnglishScore;
	}
}

std::string Student::ReturnName()
{
	return m_sStudentName;
}


Student::~Student()
{
}
