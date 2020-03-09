#include "Game.h"



Game::Game()
{
	m_iUserLife = 9;
	m_iUserAttack = 9;
	m_iUserExp = 9;
	m_iUserGold = 9;
	m_bUserStance = STANCE_DEFENCE;
	m_iUserAttack = 9;
	m_iUserLevel = 1;
}

void Game::GetName(string name)
{
	m_sUserName = name;
}

void Game::TownMenu()
{
	int iSelect;
	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		BLUE_GREEN
		gotoxy(23, 8);
		cout << "==== ���� ====";
		ORIGINAL

		gotoxy(26, 11);
		cout << "���� �Ա�";
		gotoxy(26, 13);
		cout << "���� ����";
		gotoxy(25, 15);
		cout << "���� ����";
		gotoxy(26, 17);
		cout << "���� ����";
		gotoxy(26, 19);
		cout << "�����Ѵ�";
		gotoxy(28, 21);
		cout << "����";

		iSelect = GameMap.MenuSelectCursor(6, 2, 10, 11);

		switch (iSelect)
		{
		default:
			cout << "��";
			break;
		case 2:
			ShowUserInfo();
			break;
		case 6:
			return;
		}
	}
}

void Game::ShowUserInfo()
{
	GameMap.BoxErase(WIDTH, HEIGHT);
	
	YELLOW
	gotoxy(18, 10);
	cout << "=======����� ����=======";
	ORIGINAL

	gotoxy(19, 13);
	cout << "�̸�: " << m_sUserName;
	gotoxy(19, 14);
	cout << "����: " << m_iUserLevel;
	gotoxy(19, 15);
	cout << "�����: " << m_iUserLife;
	gotoxy(19, 16);
	cout << "���ݷ�: " << m_iUserAttack;
	gotoxy(19, 17);
	cout << "����ġ: " << m_iUserExp;
	gotoxy(19, 18);
	cout << "���� ���: " << m_iUserGold;

	system("pause>null");
}

Game::~Game()
{
}
