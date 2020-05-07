#include "Play.h"
#define QUEUESIZE 11
#define INFORMATION_LINE 40

//5�� 6�� ���� �ذ� �ؾ� �ϴ� ����,,,
//�ϴٰ� ���� �̰� ���� �𸣰���
//���ڲ� �߰��� ��尡 �� �ߴ� �� �����̶� �� �ܹ��� ���Ḯ��Ʈ�̴� ������ ��������� �ٲ����
//���ϴ� ������ ������ ���� ���� �ʴ� ��
//5�� 7�� ���� �ذ� �ؾ� �ϴ� ����
//������ �ʹ� ����, �޸� ���� �߻�
//�ϴ� ���������� ��ŷ ���� �����ϰ� ����->��ũ �ؽ�Ʈ���� �������� �Ϸ���  2. ��ũ �ҷ��ͼ� ���� �� ��� 3. ������ ��� ���� ����
//���� �ϳ� ������ ���� �ϳ��� ������ ����
//�и� �����ϰ� ���ڰ� ���ͼ� ������ �����ؾ� ���� Ÿ�̸Ӱ� ���ư��µ� ����� ��� ���ư��� ������ �ֱ�

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
		cout << "����: �ܾ� �ؽ�Ʈ ������ ����";
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
	int iItemEffectTimer, iItemEffectCounter = clock();	//������ ȿ�� ���ӿ�
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
					cout << "����";	//�׽�Ʈ�� �ӽ��ڵ� �Ϸ�Ǹ� ������ ��
					break;
				}
				
				int iTmp = GameWordManager.CheckIsCorrect(sWordTyping);

				if (iTmp != NO_ACCORDING_STRING)
				{
					GameInterface.CleaningTop();
					GameWordManager.PrintEnemy();
					m_iScore += 50;
					m_iNumberOfKilledEnemy++;	
					PrintScore();	//�ùٸ��� �Է��ߴٸ� ���� �� ���� �ö󰡰� ������ ����
				}
				sWordTyping = "";

				if ((5 + 3 * m_iStageNumber) == m_iNumberOfKilledEnemy && m_iStageNumber < 10)
				{
					MoveToNextStage();	//���� ��ü���� ��ġ��� ���� �ܰ�� �Ѿ, ������ 10�ܰ谡 �����̶� �� �� �ö�(���Ѵ�� �س����� Ÿ�̸� ī���Ͱ� ��������)
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
	std::cout << "���� ����";
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
	SynopsisText.open("����ġ��_���丮.txt");

	if (SynopsisText.is_open())
	{
		ChangeColor(COLOR_BLUE);

		gotoxy(60, 27);
		cout << "��ŵ�ϱ�: SŰ";

		int iTopY = 18;	//9	//���� 10

		int iLines;	//�� �� ����

		SynopsisText >> iLines;

		string *SynopsisArr = new string[iLines];	//string �迭 ���� ������ ���پ� �� �������

		for (int i = 0; i < iLines; i++)
			getline(SynopsisText, SynopsisArr[i]);

		int iPrintLine = 0;	//��� ���� ���� 10�ٿ� �����ϸ� ����� ���۵Ǵ� �迭�� ���� �ɷ� �Ѿ �� �ְ�
		int iTopLine = 0;	//���� �� ������ �Ǿ�� �� �ε��� ��ȣ
		bool bIsEnd = false;

		while (1)
		{
			if (_kbhit())
			{
				if (_getch() == 's' || _getch() == 'S')
					break;;	//��ŵ Ű �Է½� �ó�ý� ��� �Լ� Ż��
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
		cout << "����: �ó�ý� ������ ����";
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
	cout << "����������������������������������������";
	ORIGINAL

	ChangeColor(COLOR_RED);
	gotoxy(1, INFORMATION_LINE);
	cout << "�����: ";
	gotoxy(60, INFORMATION_LINE);
	cout << "����: ";
	gotoxy(110, INFORMATION_LINE);
	cout << "�̸�: ";
	ORIGINAL
}

void Play::PrintLife()
{
	ChangeColor(COLOR_RED);
	gotoxy(9, INFORMATION_LINE);

	for (int i = 0; i < m_iLife; i++)
		cout << "��";

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
	cout << "=�̸� �Է�(����, ����)=";

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
				cout << "�̸��� 10�ڸ� �ʰ��� �� ����";
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
			cout << "���� �Ǵ� ���ڸ� �Է�";
		}
	}
}

void Play::PrintStageNumber()
{
	GameInterface.CleaningTop();
	ChangeColor(COLOR_BLUE);
	gotoxy(60, 17);
	cout << "�������� " << m_iStageNumber;
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