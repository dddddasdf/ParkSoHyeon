#pragma once
#include "Person.h"
#include "School.h"
#include "Singletone.h"
#include <Windows.h>

class Student: public Person, public School, public Singletone <Student>
{
public:
	Student();
	void GetInfo();
	void PrintInfo();
	~Student();
};

