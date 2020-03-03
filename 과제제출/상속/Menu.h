#pragma once
#include "Headers.h"
#include "Login.h"



class Menu
{
private:
	int m_iUserCount;
	Login NowLogin;
public:
	Menu();
	void PrintMenu();
	
	~Menu();
};

