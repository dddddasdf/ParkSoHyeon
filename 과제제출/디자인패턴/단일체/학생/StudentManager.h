#pragma once
#include "Student.h"
#include <list>

class StudentManager: public Singletone <StudentManager>
{
private:
	std::list <Student*> StudentList;

public:
	int GetSize();

	void NewData();
	void ShowList();
};

