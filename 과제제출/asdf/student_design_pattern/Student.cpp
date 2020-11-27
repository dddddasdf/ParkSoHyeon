#include "Student.h"
#include <string>

Student::Student()
{
	std::cout << "학생 이름 입력: ";
	std::cin >> m_sStudentName;
	std::cout << "학생 학년 입력: ";
	std::cin >> m_iGrade;
	std::cout << "학생 번호 입력: ";
	std::cin >> m_iStudentNumber;
	std::cout << "국어 성적 입력: ";
	std::cin >> m_iKoreanScore;
	std::cout << "수학 성적 입력: ";
	std::cin >> m_iMathScore;
	std::cout << "영어 성적 입력: ";
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
