#include "Game.h"
#define FEEDSPAWNTIME 1000
#define MOVINGTIME 150


Game::Game()
{
	m_BlockManager.DrawWallBlock();
	m_iScore = 0;
	PrintScore();
}

void Game::Init()
{
	m_BlockManager.SetRandObstacle();
	m_BlockManager.InitFeed();
	Player.InitSnakePosition();
	m_iFeedCount = 0;
	m_iFeedStandard = 0;
	m_iMovingStandard = 0;
	m_iFeedSpawnTimer = 0;
	m_iMovingTimer = 0;
}

void Game::StartGame()
{
	system("cls");
	int iKey = DIRECTION_NEUTRAL;	//Ű���� �Է� ������, ������ �� �߸� ����
	Player.ChangeDirection(iKey);
	m_BlockManager.DrawWallBlock();
	Init();
	PrintScore();
	Player.PrintSnake();
	m_iFeedStandard = clock();
	m_iMovingStandard = clock();
	int iSnakeX, iSnakeY;	//�� �Ӹ� ��ġ Ȯ�ο�
	int iCase;	//��Ȳ ��ȯ��

	while (1)
	{
		m_iFeedSpawnTimer = clock();
		if (m_iFeedSpawnTimer - m_iFeedStandard > FEEDSPAWNTIME)
		{
			if (m_iFeedCount < 10)
			{
				m_BlockManager.SetRandFeed(m_iFeedCount);
				m_iFeedCount++;
			}
			m_iFeedStandard = m_iFeedSpawnTimer;
		}

		if (_kbhit())
		{
			iKey = _getch();
			if (iKey == DIRECTION_LEFT || iKey == DIRECTION_RIGHT || iKey == DIRECTION_UP || iKey == DIRECTION_DOWN)
			{
				Player.ChangeDirection(iKey);
			}
		}
		
		m_iMovingTimer = clock();

		if (m_iMovingTimer - m_iMovingStandard > MOVINGTIME)
		{
			Player.MoveSnake();
			Player.PrintSnake();
			m_iMovingStandard = m_iMovingTimer;
			Player.GetSnakePosition(&iSnakeX, &iSnakeY);	//��Ӹ� ��ġ ������

			//�Ʒ��δ� ��Ȳ üũ
			iCase = m_BlockManager.IsCollisionObject(iSnakeX, iSnakeY);

			if (iCase == CASE_COLLISION_WALL)
			{
				gotoxy(40, 34);
				std::cout << "���� �ε��ļ� ���";
				Player.KillSnake();
				system("pause>null");
				return;
			}
			else if (iCase == CASE_COLLISION_OBJECT)
			{
				gotoxy(38, 34);
				std::cout << "���ع��� �ε��ļ� ���";
				Player.KillSnake();
				system("pause>null");
				return;
			}
			else if (iCase == CASE_FEED)
			{
				m_iFeedCount--;
				m_iScore++;
				Player.CreateBody();
				PrintScore();
			}

			if (Player.IsCollisionBody() == CASE_COLLISION_BODY)
			{
				gotoxy(39, 34);
				std::cout << "������ �ε��ļ� ���";
				Player.KillSnake();
				system("pause>null");
				return;
			}
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
		m_iScore = 0;
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
			m_BlockManager.DeleteBlocks();
			m_BlockManager.DeleteWallBlocks();
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
