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
			break;
		case 2:
			break;
		case 3:
			return;
		default:
			cout << "������ �޴� ��ȣ�� �Է�\n";
			break;
		}
	}
}

void Menu::DeleteUserData()
{
	
}

Menu::~Menu()
{
	if (m_iUserCount == 1)
	{
		User *tmp;

		for (int i = 0; i < m_iUserCount; i++)
		{

		}
	}
}
