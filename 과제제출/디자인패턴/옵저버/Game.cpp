#include "Game.h"

Game::Game()
{
	m_BlockManager = new BlockManager;
}

void Game::Init()
{
	Dragon = new ClearDragon;
	User = new Player("철수");

	User->SetBossAlarm(Dragon);
}

void Game::ShowGuide()
{
	gotoxy(1, 31);
	std::cout << "@: 투명드래곤\n알람 설정은 윗 방향키 종료하고 싶으면 그 외 아무 키나\n";
}

void Game::AlarmState()
{
	if (User->ReturnAlarmState)
	{
		gotoxy(1, 33);
		std::cout << "보스 알람 ON     ";
	}
	else
	{
		gotoxy(1, 33);
		std::cout << "보스 알람 OFF    ";
	}
}

void Game::NowPlaying()
{
	m_BlockManager->PrintUser();
	Init();
	ShowGuide();
	AlarmState();

	int iKey;

	while (1)
	{
		if (_kbhit())
		{
			iKey = _getch();

			if (iKey = KEYBOARD_UP)
			{
				if (User->ReturnAlarmState())
					User->TurnOffBossState();
				else
					User->GetBossState();
				AlarmState();
			}
			else return;
		}



	}
}

Game::~Game()
{
	delete m_BlockManager;
}