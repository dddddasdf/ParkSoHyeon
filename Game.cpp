#include "Game.h"
#define FEEDSPAWNTIME 1000
#define MOVINGTIME 200


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
	m_iFeedCount = 0;
	m_iFeedStandard = 0;
	m_iMovingStandard = 0;
	m_iFeedSpawnCount = 0;
	m_iMovingCount = 0;
}

void Game::StartGame()
{
	system("cls");
	int iKey = DIRECTION_NEUTRAL;	//키보드 입력 감지용, 시작할 땐 중립 상태
	Player.ChangeDirection(iKey);
	m_BlockManager.DrawWallBlock();
	Init();
	PrintScore();
	Player.PrintSnake();
	m_iFeedStandard = clock();
	m_iMovingStandard = clock();

	while (1)
	{
		/*m_iFeedSpawnCount = clock();
		if (m_iFeedSpawnCount - m_iFeedStandard > FEEDSPAWNTIME)
		{
			if (m_iFeedCount < 10)
		}*/

		if (_kbhit())
		{
			iKey = _getch();
			if (iKey == DIRECTION_LEFT || iKey == DIRECTION_RIGHT || iKey == DIRECTION_UP || iKey == DIRECTION_DOWN)
			{
				Player.ChangeDirection(iKey);
			}
		}
		
		m_iMovingCount = clock();

		if (m_iMovingCount - m_iMovingStandard > MOVINGTIME)
		{
			Player.MoveSnake();
			Player.PrintSnake();
			m_iMovingStandard = m_iMovingCount;
		}

		
	}
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
		std::cout << "1. ㄱㄱ";
		gotoxy(46, 15);
		std::cout << "2. ㄴㄴ";
		gotoxy(46, 17);
		std::cout << "선택: ";
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
			std::cout << "지정 숫자 외 입력 ㄴㄴ해";
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
