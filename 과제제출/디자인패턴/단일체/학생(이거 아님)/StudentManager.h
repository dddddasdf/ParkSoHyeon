#pragma once
#include "Student.h"
#include <string>
#include <list>

class StudentManager: public Singletone <StudentManager>
{
private:
	std::list <Student*> StudentList;

public:
	StudentManager();
	int GetSize();

	void NewData();
	void ShowList();

	~StudentManager();
};

