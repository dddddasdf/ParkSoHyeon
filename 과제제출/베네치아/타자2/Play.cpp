#include "Play.h"
#define QUEUESIZE 11
#define INFORMATION_LINE 40
#define MAX_STAGE 10
#define HIDING_TIME 1500
#define VELOCITY_TIME 2000


Play::Play()
{

}

void Play::PlayMain(string &NameTmp, int &ScoreTmp, int &StageTmp)
{
	Init();
	if (GameWordManager.LoadWordTextFile() == false)
	{
		ChangeColor(COLOR_RED);
		gotoxy(38, 17);
		cout << "에러: 단어 텍스트 파일이 없음";
		return;
	}

	PrintSynopsis();

	GetName();
	PrintBottomArea();
	PrintLife();
	PrintScore();
	PrintName();

	PrintStageNumber();
	GameInterface.CleaningTop();

	int iMovingTimer = 0, iMovingCounter = clock();
	int iSlowEffectTimer = 0, iSlowEffectCounter = 0;	//아이템-느리게 효과 지속용
	int iFastEffectTimer = 0, iFastEffectCounter = 0;	//아이템-빠르게 효과 지속용
	int iStopEffectTimer = 0, iStopEffectCounter = 0;	//아이템-멈춤 효과 지속용
	int iHidingEffectTimer = 0, iHidingEffectCounter = 0;	//아이템-감추기 효과 지속용
	string sWordTyping = "";
	char cInputChar;
	bool bIsFast = false;
	bool bIsSlow = false;
	bool bIsStop = false;
	bool bIsHiding = false;

	while (m_iLife != 0)
	{
		if (_kbhit())
		{
			cInputChar = _getch();

			CleanParticularArea(55, 75, HORIZON + 2, HORIZON + 2);

			if (cInputChar == KEYBOARD_ENTER)
			{				
				int iTmp = GameWordManager.CheckIsCorrect(sWordTyping);

				if (iTmp != NO_ACCORDING_STRING)
				{
					m_iScore += 50;
					m_iNumberOfKilledEnemy++;	
					PrintScore();	//올바르게 입력했다면 잡은 몹 숫자 올라가고 점수도 쌓임
				}
				sWordTyping = "";

				if ((5 + 3 * m_iStageNumber) == m_iNumberOfKilledEnemy && m_iStageNumber < MAX_STAGE)
				{
					GameInterface.CleaningTop();
					MoveToNextStage();	//일정 개체수를 해치우면 다음 단계로 넘어감, 하지만 10단계가 최종이라 더 안 올라감(무한대로 해놓으면 타이머 카운터가 망가진다)
					GameWordManager.ClearWords();
					continue;
				}

				//아이템 발동 목록
				if (iTmp == ITEM_SLOW)
				{
					bIsSlow = true;
					m_iMovingSpeed = 800;
					iSlowEffectCounter = clock();
					iSlowEffectTimer = clock();
				}
				else if (iTmp == ITEM_FAST)
				{
					bIsFast = true;
					m_iMovingSpeed = 200;
					iFastEffectCounter = clock();
					iFastEffectTimer = clock();
				}
				else if (iTmp == ITEM_STOP)
				{
					bIsStop = true;
					iStopEffectCounter = clock();
					iStopEffectTimer = clock();
				}
				else if (iTmp == ITEM_DELETE_ALL)
				{
					GameInterface.CleaningTop();
					GameWordManager.ClearWords();
				}
				else if (iTmp == ITEM_HIDE)
				{
					bIsHiding = true;
					GameWordManager.PrintEnemy(bIsHiding);
					iHidingEffectCounter = clock();
					iHidingEffectTimer = clock();
				}
				//아이템 발동 목록 끝
			}
			else if (cInputChar == KEYBOARD_BACKSPACE)
			{
				if (sWordTyping != "")
				{
					sWordTyping.erase(sWordTyping.length() - 1);
					ChangeColor(COLOR_BLUE_GREEN);
					gotoxy(WIDTH - (sWordTyping.length() / 2), HORIZON + 2);
					cout << sWordTyping;
					ORIGINAL
				}
			}
			else
			{
				ChangeColor(COLOR_BLUE_GREEN);
				sWordTyping += cInputChar;
				gotoxy(WIDTH - (sWordTyping.length() / 2), HORIZON + 2);
				cout << sWordTyping;
				ORIGINAL
			}
		}

		//아이템 지속시간 체크 시작
		if (bIsSlow == true)
		{
			iSlowEffectTimer = clock();
			if (iSlowEffectTimer - iSlowEffectCounter >= VELOCITY_TIME)
			{
				bIsSlow = false;
				iSlowEffectCounter = iSlowEffectTimer;
				m_iMovingSpeed = 600 - 30 * (m_iStageNumber - 1);
			}
		}

		if (bIsFast == true)
		{
			iFastEffectTimer = clock();
			if (iFastEffectTimer - iFastEffectCounter >= VELOCITY_TIME)
			{
				bIsSlow = false;
				iFastEffectCounter = iFastEffectTimer;
				m_iMovingSpeed = 600 - 30 * (m_iStageNumber - 1);
			}
		}

		if (bIsStop == true)
		{
			iStopEffectTimer = clock();
			if (iStopEffectTimer - iStopEffectCounter >= VELOCITY_TIME)
			{
				bIsStop = false;
				iStopEffectCounter = iStopEffectTimer;
			}
		}
		else
			iMovingTimer = clock();

		if (bIsHiding == true)
		{
			iHidingEffectTimer = clock();
			if (iHidingEffectTimer - iHidingEffectCounter >= HIDING_TIME)
			{
				bIsHiding = false;
				m_iMovingSpeed = 600 - 50 * (m_iStageNumber - 1);
				iHidingEffectCounter = iHidingEffectTimer;
			}
		}
		//아이템 지속 시간 체크 끝

		if (iMovingTimer - iMovingCounter > m_iMovingSpeed)
		{
			int iTmp = 0;
			iTmp = rand() % 100;

			if (iTmp <= 10 * m_iStageNumber)
				GameWordManager.CreatNewEnemy();
			
			bool bTmp;
			bTmp = GameWordManager.MoveEnemy();
			GameWordManager.PrintEnemy(bIsHiding);
			iMovingCounter = iMovingTimer;

			if (bTmp == true)
			{
				m_iLife--;
				CleanParticularArea((9 + m_iLife * 2), (9 + (m_iLife + 1) * 2), INFORMATION_LINE, INFORMATION_LINE);
				PrintLife();
			}
		}
	}

	GameInterface.CleaningTop();
	gotoxy(61, (HEIGHT) / 2);
	ChangeColor(COLOR_BLOOD);
	std::cout << "게임 오버";
	ORIGINAL
	Sleep(1000);

	NameTmp = m_sUserName;
	ScoreTmp = m_iScore;
	StageTmp = m_iStageNumber;

	GameWordManager.DeleteStringArray();
}

void Play::PrintSynopsis()
{
	GameInterface.CleaningTop();

	ifstream SynopsisText;
	SynopsisText.open("베네치아_스토리.txt");

	if (SynopsisText.is_open())
	{
		ChangeColor(COLOR_BLUE);

		gotoxy(60, 27);
		cout << "스킵하기: S키";

		int iTopY = 18;	//9	//길이 10

		int iLines;	//총 줄 개수

		SynopsisText >> iLines;

		string *SynopsisArr = new string[iLines];	//string 배열 만들어서 깡으로 한줄씩 다 집어넣음

		for (int i = 0; i < iLines; i++)
			getline(SynopsisText, SynopsisArr[i]);

		int iPrintLine = 0;	//출력 중인 줄이 10줄에 도달하면 출력이 시작되는 배열이 다음 걸로 넘어갈 수 있게
		int iTopLine = 0;	//현재 맨 윗줄이 되어야 할 인덱스 번호
		bool bIsEnd = false;

		while (1)
		{
			if (_kbhit())
			{
				if (_getch() == 's' || _getch() == 'S')
					break;;	//스킵 키 입력시 시놉시스 출력 함수 탈출
			}

			Sleep(500);
			CleanParticularArea(30, 100, 8, 19);

			if (iPrintLine < 10)
			{
				int YTmp = 0;
				for (int i = iTopLine; i <= iPrintLine; i++)
				{
					gotoxy(WIDTH - (SynopsisArr[i].length() / 2), iTopY + YTmp);
					cout << SynopsisArr[i];
					YTmp++;
				}
				if (iTopY > 9)
					iTopY--;
				iPrintLine++;
			}
			else if (iPrintLine >= 10 && iPrintLine < (iLines - 10))
			{
				iTopLine++;
				int YTmp = 0;
				for (int i = iTopLine; i <= iPrintLine; i++)
				{
					gotoxy(WIDTH - (SynopsisArr[i].length() / 2), iTopY + YTmp);
					cout << SynopsisArr[i];
					YTmp++;
				}
				iPrintLine++;
			}
			else
			{
				iTopLine++;
				int YTmp = 0;
				for (int i = iTopLine; i <= iPrintLine; i++)
				{
					gotoxy(WIDTH - (SynopsisArr[i].length() / 2), iTopY + YTmp);
					cout << SynopsisArr[i];
					YTmp++;	
				}
				if (iPrintLine != (iLines - 1))
					iPrintLine++;
				if (iTopLine == iLines)
					break;
			}
		}

		delete[] SynopsisArr;

		CleanParticularArea(15, 50, 8, 19);

		ORIGINAL
	}
	else
	{
		ChangeColor(COLOR_RED);
		gotoxy(40, 17);
		cout << "에러: 시놉시스 파일이 없음";
	}
}

void Play::CleanParticularArea(int StartX, int EndX, int StartY, int EndY)
{
	for (int y = StartY; y <= EndY; y++)
	{
		for (int x = StartX; x <= EndX; x++)
		{
			gotoxy(x, y);
			cout << "  ";
		}
	}
}

void Play::Init()
{
	m_iLife = 10;
	m_iScore = 0;
	m_sUserName = "\? \? \?";
	m_iStageNumber = 1;
	m_iNumberOfKilledEnemy = 0;
	m_iSpawnSpeed = 2500;
	m_iMovingSpeed = 600;
}

void Play::PrintBottomArea()
{
	gotoxy(55, HORIZON + 3);
	ChangeColor(COLOR_BLUE_GREEN);
	cout << "────────────────────";
	ORIGINAL

	ChangeColor(COLOR_RED);
	gotoxy(1, INFORMATION_LINE);
	cout << "생명력: ";
	gotoxy(60, INFORMATION_LINE);
	cout << "점수: ";
	gotoxy(110, INFORMATION_LINE);
	cout << "이름: ";
	ORIGINAL
}

void Play::PrintLife()
{
	ChangeColor(COLOR_RED);
	gotoxy(9, INFORMATION_LINE);

	for (int i = 0; i < m_iLife; i++)
		cout << "♥";

	ORIGINAL
}

void Play::PrintScore()
{
	ChangeColor(COLOR_RED);

	gotoxy(66, INFORMATION_LINE);
	cout << m_iScore;

	ORIGINAL
}

void Play::PrintName()
{
	ChangeColor(COLOR_RED);

	gotoxy(116, INFORMATION_LINE);
	cout << m_sUserName;

	ORIGINAL;
}

void Play::GetName()
{
	GameInterface.CleaningTop();

	ChangeColor(COLOR_BLUE);
	gotoxy(53, 12);
	cout << "=이름 입력(영문, 숫자)=";

	string sNameTmp;
	char cInputChar;
	int iNameTmpLen = 0;

	while (1)
	{
		cInputChar = _getch();

		CleanParticularArea(50, 80, 15, 19);


		if ((cInputChar >= '0' && cInputChar <= '9') || (cInputChar >= 'A' && cInputChar <= 'Z')
			|| (cInputChar >= 'a' && cInputChar <= 'z'))
		{
			if (sNameTmp.length() == 10)
			{
				ChangeColor(COLOR_BLUE);
				gotoxy(WIDTH - (sNameTmp.length() / 2), 16);
				cout << sNameTmp;
				ChangeColor(COLOR_RED);
				gotoxy(50, 19);
				cout << "이름은 10자를 초과할 수 없음";
			}
			else
			{
				ChangeColor(COLOR_BLUE);
				sNameTmp += cInputChar;
				gotoxy(WIDTH - (sNameTmp.length() / 2), 16);
				cout << sNameTmp;
			}
		}
		else if (cInputChar == KEYBOARD_ENTER)
		{
			if (sNameTmp == "")
				sNameTmp = "AAA";
			m_sUserName = sNameTmp;
			ORIGINAL
			return;
		}
		else if (cInputChar == KEYBOARD_BACKSPACE)
		{
			if (sNameTmp != "")
			{
				sNameTmp.erase(sNameTmp.length() - 1);
				ChangeColor(COLOR_BLUE);
				gotoxy(WIDTH - (sNameTmp.length() / 2), 16);
				cout << sNameTmp;
			}
		}
		else
		{
			ChangeColor(COLOR_BLUE);
			gotoxy(WIDTH - (sNameTmp.length() / 2), 16);
			cout << sNameTmp;
			ChangeColor(COLOR_RED);
			gotoxy(54, 19);
			cout << "영문 또는 숫자만 입력";
		}
	}
}

void Play::PrintStageNumber()
{
	GameInterface.CleaningTop();
	ChangeColor(COLOR_BLUE);
	gotoxy(60, 17);
	cout << "스테이지 " << m_iStageNumber;
	ORIGINAL

	Sleep(1000);

	CleanParticularArea(60, 75, 17, 17);
}

void Play::MoveToNextStage()
{
	CleanParticularArea(66, 75, INFORMATION_LINE, INFORMATION_LINE);
	m_iScore = 0;
	m_iNumberOfKilledEnemy = 0;
	m_iStageNumber++;
	PrintScore();
	PrintStageNumber();
	m_iSpawnSpeed -= 100;
	m_iMovingSpeed = 600 - 30 * (m_iStageNumber - 1);
}

Play::~Play()
{

}