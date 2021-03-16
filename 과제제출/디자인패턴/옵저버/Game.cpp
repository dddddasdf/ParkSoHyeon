#include "Game.h"

Game::Game()
{
	m_BlockManager = new BlockManager;
}

void Game::Init()
{
	Dragon = new ClearDragon;
	User = new Player("ö��");

	User->SetBossAlarm(Dragon);
}

void Game::ShowGuide()
{
	gotoxy(1, 31);
	std::cout << "@: ����巡��\n�˶� ������ �� ����Ű �����ϰ� ������ �� �� �ƹ� Ű��\n";
}

void Game::AlarmState()
{
	if (User->ReturnAlarmState)
	{
		gotoxy(1, 33);
		std::cout << "���� �˶� ON     ";
	}
	else
	{
		gotoxy(1, 33);
		std::cout << "���� �˶� OFF    ";
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