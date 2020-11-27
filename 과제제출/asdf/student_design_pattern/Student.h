#pragma once
#include "Singletone.h"
#include <Windows.h>
#include <vector>
#include <list>

enum INFOTYPE
{
	INFO_GRADE,
	INFO_NUMBER,
	INFO_KOREANSCORE,
	INFO_MATHSCORE,
	INFO_ENGLISHSCORE
};

class Student
{
private:
	int m_iGrade;
	int m_iStudentNumber;
	std::string m_sStudentName;
	int m_iKoreanScore;
	int m_iMathScore;
	int m_iEnglishScore;
public:
	Student();
	int ReturnValue(int StudentInfoType);
	std::string ReturnName();
	~Student();
};

