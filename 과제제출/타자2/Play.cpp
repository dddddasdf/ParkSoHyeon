#include "Play.h"
#define QUEUESIZE 11

//4월 20일 진행도: 이름 입력 받아서 실시간으로 뭐 썼나 보여줘ㄷ야 됨
Play::Play()
{

}

void Play::PlayMain()
{
	Init();
	PrintSynopsis();

	GetName();
	PrintBottomArea();
	PrintLife();
	PrintScore();
	PrintName();

	PrintStageNumber();
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
		char cIsSkip;

		int iLines;

		SynopsisText >> iLines;

		string *SynopsisArr = new string[iLines];	//string 배열 만들어서 깡으로 한줄씩 다 집어넣음

		for (int i = 0; i < iLines; i++)
			getline(SynopsisText, SynopsisArr[i]);

		int iPrintLine = 0;	//출력 중인 줄이 10줄에 도달하면 출력이 시작되는 배열이 다음 걸로 넘어갈 수 있게

		for (int i = 0; i < iLines; i++)
		{
			Sleep(800);
			CleanParticularArea(30, 100, 8, 19);
			if (_kbhit())
			{
				cIsSkip = _getch();
				if (cIsSkip == 'S' || cIsSkip == 's')
				{
					delete[] SynopsisArr;
					return;
				}
			}
			if (i < 10)
			{
				int YTmp = 0;
				for (int j = iPrintLine; j <= i; j++)
				{
					gotoxy(WIDTH - (SynopsisArr[j].length() / 2), iTopY + YTmp);
					cout << SynopsisArr[j];
					YTmp++;
				}
				if (iTopY > 9)
					iTopY--;
			}
			else
			{
				iPrintLine++;
				int YTmp = 0;
				for (int j = iPrintLine; j <= i; j++)
				{
					gotoxy(WIDTH - (SynopsisArr[j].length() / 2), iTopY + YTmp);
					cout << SynopsisArr[j];
					YTmp++;
				}
			}
		}

		//앞으로 출력해야 하는 줄이 10줄 이하
		for (int i = 1; i < 10; i++)
		{
			Sleep(800);
			CleanParticularArea(30, 100, 8, 19);
			if (_kbhit())
			{
				cIsSkip = _getch();
				if (cIsSkip == 'S' || cIsSkip == 's')
				{
					delete[] SynopsisArr;
					return;
				}
			}
			int YTmp = 0;
			for (int j = iLines - (10 - i); j < iLines; j++)
			{
				gotoxy(WIDTH - (SynopsisArr[j].length() / 2), iTopY + YTmp);
				cout << SynopsisArr[j];
				YTmp++;
			}
		}

		delete[] SynopsisArr;

		Sleep(800);
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

//void Play::CleaningSynopsisArea()
//{
//	시놉시스 출력 구간 청소
//	for (int y = 8; y < 19; y++)
//	{
//		for (int x = 15; x < 50; x++)
//		{
//			gotoxy(x * 2, y);
//			cout << "  ";
//		}
//	}
//}

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
}

void Play::PrintBottomArea()
{
	ChangeColor(COLOR_RED);

	gotoxy(1, HORIZON + 2);
	cout << "생명력: ";
	gotoxy(60, HORIZON + 2);
	cout << "점수: ";
	gotoxy(110, HORIZON + 2);
	cout << "이름: ";

	ORIGINAL
}

void Play::PrintLife()
{
	ChangeColor(COLOR_RED);
	gotoxy(9, HORIZON + 2);

	for (int i = 0; i < m_iLife; i++)
		cout << "♥";

	ORIGINAL
}

void Play:: PrintScore()
{
	ChangeColor(COLOR_RED);

	gotoxy(66, HORIZON + 2);
	cout << m_iScore;

	ORIGINAL
}

void Play::PrintName()
{
	ChangeColor(COLOR_RED);

	gotoxy(116, HORIZON + 2);
	cout << m_sUserName;

	ORIGINAL;
}

void Play::GetName()
{
	GameInterface.CleaningTop();

	ChangeColor(COLOR_BLUE);
	gotoxy(54, 12);
	cout << "이름 입력(영문, 숫자)";

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
			m_sUserName = sNameTmp;
			ORIGINAL
			return;
		}
		else if (cInputChar == KEYBOARD_BACKSPACE)
		{
			sNameTmp.erase(sNameTmp.length() - 1);
			ChangeColor(COLOR_BLUE);
			gotoxy(WIDTH - (sNameTmp.length() / 2), 16);
			cout << sNameTmp;
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

Play::~Play()
{

}