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
		cout << "=====�޴�=====(ȸ����[" << m_iUserCount << "��])\n";
		cout << "   1. ȸ�� ����\n";
		cout << "   2. �α���\n";
		cout << "   3. ����\n";
		cout << "�Է�: ";
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
			cout << "������ �޴� ��ȣ�� �Է�\n";
			break;
		}
	}
}

Menu::~Menu()
{

}
