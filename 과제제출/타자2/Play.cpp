#include "Play.h"
#define QUEUESIZE 11
#define INFORMATION_LINE 40

//5월 6일 지금 해결 해야 하는 문제,,,
//하다가 뻗음 이건 이유 모르겠음
//ㄴ자꾸 중간에 노드가 붕 뜨는 게 원인이라 걍 단방향 연결리스트이던 구조를 양방향으로 바꿔버림
//ㄴ일단 지금은 별도로 에러 뱉지 않는 듯
//5월 7일 지금 해결 해야 하는 문제
//깜빡임 너무 심함, 메모리 누수 발생
//일단 스테이지와 랭킹 구현 마저하고 보자->랭크 텍스트파일 생성까진 완료함  2. 랭크 불러와서 정렬 후 출력 3. 아이템 기능 구현 남음
//문제 하나 잡으면 문제 하나가 나오는 기적
//분명 랜덤하게 숫자가 나와서 조건을 만족해야 스폰 타이머가 돌아가는데 좆까고 계속 돌아간다 이유가 멀까

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

	int iSpawnTimer = clock(), iSpawnCounter = clock();
	int iMovingTimer = 0, iMovingCounter = clock();
	int iItemEffectTimer, iItemEffectCounter = clock();	//아이템 효과 지속용
	string sWordTyping = "";
	char cInputChar;

	while (m_iLife != 0)
	{
		int iTmp = 0;
		iTmp = rand() % 1000;
		
		if (iTmp <= 10 * m_iStageNumber)
		{
			iSpawnTimer = clock();
			
		}

		iMovingTimer = clock();

		if (_kbhit())
		{
			cInputChar = _getch();

			CleanParticularArea(55, 75, HORIZON + 2, HORIZON + 2);

			if (cInputChar == KEYBOARD_ENTER)
			{
				if (sWordTyping == "")
				{
					cout << "자폭";	//테스트용 임시코드 완료되면 삭제할 것
					break;
				}
				
				int iTmp = GameWordManager.CheckIsCorrect(sWordTyping);

				if (iTmp != NO_ACCORDING_STRING)
				{
					GameInterface.CleaningTop();
					GameWordManager.PrintEnemy();
					m_iScore += 50;
					m_iNumberOfKilledEnemy++;	
					PrintScore();	//올바르게 입력했다면 잡은 몹 숫자 올라가고 점수도 쌓임
				}
				sWordTyping = "";

				if ((5 + 3 * m_iStageNumber) == m_iNumberOfKilledEnemy && m_iStageNumber < 10)
				{
					MoveToNextStage();	//일정 개체수를 해치우면 다음 단계로 넘어감, 하지만 10단계가 최종이라 더 안 올라감(무한대로 해놓으면 타이머 카운터가 망가진다)
					GameWordManager.ClearWords();
					continue;
				}
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

		if (iSpawnTimer - iSpawnCounter > m_iSpawnSpeed)
		{
			GameWordManager.CreatNewEnemy();
			iSpawnCounter = iSpawnTimer;
		}

		if (iMovingTimer - iMovingCounter > m_iMovingSpeed)
		{
			bool bTmp;
			bTmp = GameWordManager.MoveEnemy();
			GameInterface.CleaningTop();
			GameWordManager.PrintEnemy();
			iMovingCounter = iMovingTimer;

			cout << iTmp;

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
	m_iLife = 9;
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
}

void Play::MoveToNextStage()
{
	CleanParticularArea(66, 75, INFORMATION_LINE, INFORMATION_LINE);
	m_iScore = 0;
	m_iNumberOfKilledEnemy = 0;
	m_iStageNumber++;
	PrintStageNumber();
	m_iSpawnSpeed -= 100;
	m_iMovingSpeed -= 50;
}

Play::~Play()
{

}