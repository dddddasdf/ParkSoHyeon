#include "Game.h"

Game::Game()
{
	m_BlockManager = new BlockManager;
}

void Game::Init()
{
	Dragon = new ClearDragon;
	User = new Player("ö��");
	m_iDragonSpawnTime = 1500;	//���� �ֱ�

	User->SetBossAlarm(Dragon);
}

void Game::ShowGuide()
{
	gotoxy(0, 20);
	std::cout << "@: ����巡��\n�˶� ������ SŰ �����ϰ� ������ �� �� �ƹ� Ű��\n";
}

void Game::AlarmState()
{
	if (User->ReturnAlarmState())
	{
		gotoxy(0, 22);
		std::cout << "���� �˶� ON     ";
	}
	else
	{
		gotoxy(0, 22);
		std::cout << "���� �˶� OFF    ";
		gotoxy(0, 23);
		std::cout << "                    ";
	}
}

void Game::NowPlaying()
{
	m_BlockManager->PrintUser();
	Init();
	ShowGuide();
	
	AlarmState();

	int iKey;
	int iSpawnTimer = 0, iSpawnCounter = clock();

	while (1)
	{
		iSpawnTimer = clock();

		if (iSpawnTimer - iSpawnCounter > m_iDragonSpawnTime)
		{
			if (Dragon->ReturnBossState())
				Dragon->DisappearBoss();
			else
				Dragon->SpawnBoss();

			iSpawnCounter = iSpawnTimer;
		}
		
		if (_kbhit())
		{
			iKey = _getch();

			if (iKey == 's' || iKey == 'S')
			{
				if (User->ReturnAlarmState())
					User->TurnOffBossState();
				else
					User->GetBossState();
				AlarmState();
			}
			else
				return;
		}
	}
}

Game::~Game()
{
	delete m_BlockManager;
}