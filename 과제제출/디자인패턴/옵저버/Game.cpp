#include "Game.h"

Game::Game()
{
	m_BlockManager = new BlockManager;
}

void Game::Init()
{
	Dragon = new ClearDragon;
	User = new Player("철수");
	m_iDragonSpawnTime = 1500;	//리젠 주기

	User->SetBossAlarm(Dragon);
}

void Game::ShowGuide()
{
	gotoxy(0, 20);
	std::cout << "@: 투명드래곤\n알람 설정은 S키 종료하고 싶으면 그 외 아무 키나\n";
}

void Game::AlarmState()
{
	if (User->ReturnAlarmState())
	{
		gotoxy(0, 22);
		std::cout << "보스 알람 ON     ";
	}
	else
	{
		gotoxy(0, 22);
		std::cout << "보스 알람 OFF    ";
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