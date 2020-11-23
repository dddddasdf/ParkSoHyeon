#include "Student.h"



Student::Student()
{
}

void Student::GetInfo()
{
	GetSchool();
	GetPerson();
}

void Student::PrintInfo()
{
	system("cls");
	PrintSchool();
	PrintPerson();
}

Student::~Student()
{
}
