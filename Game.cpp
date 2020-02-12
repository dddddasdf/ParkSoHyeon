#include "Game.h"



Game::Game()
{
	m_BlockManager.DrawWallBlock();
	m_iScore = 0;
	PrintScore();
	//MapDraw();
}

void Game::Init()
{
	m_BlockManager.SetRandObstacle();
}

void Game::StartGame()
{
	system("cls");
	m_BlockManager.DrawWallBlock();
	Init();
	PrintScore();
	system("pause>null");
}

void Game::PrintScore()
{
	gotoxy(44, 32);
	std::cout << "Score: " << m_iScore;
}

void Game::Menu()
{
	int iSelect = 0;
	
	while (1)
	{
		gotoxy(46, 13);
		std::cout << "1. ����";
		gotoxy(46, 15);
		std::cout << "2. ����";
		gotoxy(46, 17);
		std::cout << "����: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		case 1:
			StartGame();
			system("cls");
			m_BlockManager.DrawWallBlock();
			PrintScore();
			break;
		case 2:
			return;
		default:
			gotoxy(30, 18);
			std::cout << "���� ���� �� �Է� ������";
			system("pause>null");
			system("cls");
			m_BlockManager.DrawWallBlock();
			PrintScore();
			break;
		}
	}
}

Game::~Game()
{
}
