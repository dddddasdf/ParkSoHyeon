#include "Rank.h"

Rank::Rank()
{

}

void Rank::LoadRankingFile()
{
	ifstream RankFile;
	RankFile.open("Rank.txt");

	if (!RankFile.is_open())
	{
		ChangeColor(COLOR_RED);
		gotoxy(38, 17);
		cout << "에러: 랭킹 텍스트 파일이 없음";
		return;
	}

	m_iNumberofStruct = 0;
	
	while (!RankFile.eof())
	{
		string Tmp;
		getline(RankFile, Tmp);
		m_iNumberofStruct++;
	}

	m_iNumberofStruct--;

	RankFile.close();

	RankFile.open("Rank.txt");

	UserStructs = new UserInformation[m_iNumberofStruct];

	for (int i = 0; i < m_iNumberofStruct; i++)
		RankFile >> UserStructs[i].sName >> UserStructs[i].iScore >> UserStructs[i].iStageNumber;

	
	RankFile.close();
}

void Rank::SortRanking()
{
	for (int i = 0; i < m_iNumberofStruct - 1; i++)
	{
		for (int j = i + 1; j < m_iNumberofStruct; j++)
		{
			if (UserStructs[i].iStageNumber < UserStructs[j].iStageNumber)
			{
				UserInformation Tmp = UserStructs[i];
				UserStructs[i] = UserStructs[j];
				UserStructs[j] = Tmp;
			}
		}
	}
	//먼저 스테이지순으로 정렬

	for (int i = 0; i < m_iNumberofStruct - 1; i++)
	{
		for (int j = i + 1; j < m_iNumberofStruct; j++)
		{
			if (UserStructs[i].iStageNumber == UserStructs[j].iStageNumber)
			{
				if (UserStructs[i].iScore < UserStructs[j].iScore)
				{
					UserInformation Tmp = UserStructs[i];
					UserStructs[i] = UserStructs[j];
					UserStructs[j] = Tmp;
				}
			}
		}
	}
	//그 다음 스코어순으로 정렬
}

void Rank::ShowRanking()
{
	LoadRankingFile();
	SortRanking();
	
	RankInterface.CleaningTop();

	ChangeColor(COLOR_BLUE_GREEN);
	gotoxy(63, 5);
	cout << "랭 킹";
	ORIGINAL

	int iYPositionTmp = 9;
	ChangeColor(COLOR_BLUE_GREEN);
	gotoxy(40, iYPositionTmp);
	cout << "이 름";
	gotoxy(64, iYPositionTmp);
	cout << "점 수";
	gotoxy(88, iYPositionTmp);
	cout << "스테이지";
	ORIGINAL

	iYPositionTmp += 2;

	if (m_iNumberofStruct < 10)
	{
		ChangeColor(COLOR_BLUE_GREEN);
		for (int i = 0; i < m_iNumberofStruct; i++)
		{
			gotoxy(40, iYPositionTmp);
			cout << UserStructs[i].sName;
			gotoxy(64, iYPositionTmp);
			cout << UserStructs[i].iScore;
			gotoxy(88, iYPositionTmp);
			cout << UserStructs[i].iStageNumber;
			iYPositionTmp += 2;
		}
		ORIGINAL
	}
	else
	{
		ChangeColor(COLOR_BLUE_GREEN);
		for (int i = 0; i < 10; i++)
		{
			gotoxy(40, iYPositionTmp);
			cout << UserStructs[i].sName;
			gotoxy(64, iYPositionTmp);
			cout << UserStructs[i].iScore;
			gotoxy(88, iYPositionTmp);
			cout << UserStructs[i].iStageNumber;
			iYPositionTmp += 2;
		}
		ORIGINAL
	}

	system("pause>null");

	FreeDynamicArrays();
}

void Rank::FreeDynamicArrays()
{
	delete[] UserStructs;
}

void Rank::GetNameAndScore(string Name, int Score, int Stage)
{
	ofstream RankFile;
	RankFile.open("Rank.txt", ios::app);

	if (RankFile.is_open())
		RankFile << Name << " " << Score << " " << Stage << "\n";

	RankFile.close();
}

Rank::~Rank()
{

}