#pragma once
#include "Person.h"
#include "School.h"
#include "Singletone.h"
#include <Windows.h>
#include <vector>
#include <list>

class Student: public Person, public School
{
private:

public:
	Student();
	void GetInfo();
	void PrintInfo();
	~Student();
};

