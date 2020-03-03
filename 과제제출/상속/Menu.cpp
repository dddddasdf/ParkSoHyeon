#include "Menu.h"



Menu::Menu()
{
	m_iUserCount = 0;
}

void Menu::PrintMenu()
{
	int iSelect;

	while (1)
	{
		system("cls");
		cout << "=====메뉴=====(회원수[" << m_iUserCount << "명])\n";
		cout << "   1. 회원 가입\n";
		cout << "   2. 로그인\n";
		cout << "   3. 종료\n";
		cout << "입력: ";
		cin >> iSelect;

		switch (iSelect)
		{
		case 1:
			NowLogin.Register(m_iUserCount);
			m_iUserCount++;
			break;
		case 2:
			NowLogin.DataCheck();
			break;
		case 3:
			return;
		default:
			cout << "지정된 메뉴 번호만 입력\n";
			break;
		}
	}
}

Menu::~Menu()
{

}
