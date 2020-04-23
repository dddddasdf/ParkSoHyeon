#include "Play.h"
#define QUEUESIZE 11

//4�� 20�� ���൵: �̸� �Է� �޾Ƽ� �ǽð����� �� �質 �����ध�� ��
Play::Play()
{

}

void Play::PlayMain()
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
	GameWordManager.DeleteStringArr();
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

//void Play::CleaningSynopsisArea()
//{
//	�ó�ý� ��� ���� û��
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
	cout << "�����: ";
	gotoxy(60, HORIZON + 2);
	cout << "����: ";
	gotoxy(110, HORIZON + 2);
	cout << "�̸�: ";

	ORIGINAL
}

void Play::PrintLife()
{
	ChangeColor(COLOR_RED);
	gotoxy(9, HORIZON + 2);

	for (int i = 0; i < m_iLife; i++)
		cout << "��";

	ORIGINAL
}

void Play::PrintScore()
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

Play::~Play()
{

}