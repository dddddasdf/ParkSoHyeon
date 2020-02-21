#pragma once
#include "Headers.h"

struct User
{
	string Id;
	string Password;
	int Age;
	int PhoneNumber;
	int Mileage;
	User *Next;
};

class Menu
{
private:
	int m_iUserCount;
public:
	Menu();
	void PrintMenu();
	void DeleteUserData();
	~Menu();
};

