#pragma once
#include "Person.h"
#include "School.h"
#include <Windows.h>

class Student: public Person, public School
{
public:
	Student();
	void GetInfo();
	void PrintInfo();
	~Student();
};

