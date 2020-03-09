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
		cout << "==== 마을 ====";
		ORIGINAL

		gotoxy(26, 11);
		cout << "던전 입구";
		gotoxy(26, 13);
		cout << "유저 정보";
		gotoxy(25, 15);
		cout << "몬스터 정보";
		gotoxy(26, 17);
		cout << "무기 상점";
		gotoxy(26, 19);
		cout << "저장한다";
		gotoxy(28, 21);
		cout << "종료";

		iSelect = GameMap.MenuSelectCursor(6, 2, 10, 11);

		switch (iSelect)
		{
		default:
			cout << "댕";
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
	cout << "=======당신의 정보=======";
	ORIGINAL

	gotoxy(19, 13);
	cout << "이름: " << m_sUserName;
	gotoxy(19, 14);
	cout << "레벨: " << m_iUserLevel;
	gotoxy(19, 15);
	cout << "생명력: " << m_iUserLife;
	gotoxy(19, 16);
	cout << "공격력: " << m_iUserAttack;
	gotoxy(19, 17);
	cout << "경험치: " << m_iUserExp;
	gotoxy(19, 18);
	cout << "소지 골드: " << m_iUserGold;

	system("pause>null");
}

Game::~Game()
{
}
