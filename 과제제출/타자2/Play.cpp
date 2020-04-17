#include "Play.h"

Play::Play()
{

}

void Play::PlayMain()
{
	PrintSynopsis();
}

void Play::PrintSynopsis()
{
	GameInterface.CleaningTop();

	ifstream SynopsisText;
	SynopsisText.open("베네치아_스토리.txt");

	if (SynopsisText.is_open())
	{
		string sNewReading, sTmp1, sTmp2, sTmpWhole;
		int iTopY = 18;


		/*ChangeColor(COLOR_BLUE);

		getline(SynopsisText, sNewReading);
		gotoxy(WIDTH - (sNewReading.length() / 2), 18);
		cout << sNewReading;

		Sleep(1000);
		CleaningSynopsisArea();
		iTopY--;
		sTmp1 = sNewReading;
		getline(SynopsisText, sNewReading);
		gotoxy(WIDTH - (sTmp1.length() / 2), iTopY);
		cout << sTmp1;
		gotoxy(WIDTH - (sNewReading.length() / 2), 18);
		cout << sNewReading;

		Sleep(1000);
		CleaningSynopsisArea();
		iTopY--;
		gotoxy(WIDTH - (sTmp1.length() / 2), iTopY);
		cout << sTmp1;
		sTmp2 = sTmp1;
		sTmp1 = sNewReading;
		gotoxy(WIDTH - (sTmp1.length() / 2), iTopY + 1);
		cout << sTmp1;
		getline(SynopsisText, sNewReading);
		gotoxy(WIDTH - (sNewReading.length() / 2), 18);
		cout << sNewReading;



		while (!SynopsisText.eof())
		{
			Sleep(1000);
			CleaningSynopsisArea();
			iTopY--;
			gotoxy(WIDTH - (sTmp2.length() / 2), iTopY);
			cout << sTmp1;
			sTmp2 = sTmp1;
			sTmp1 = sNewReading;
			gotoxy(WIDTH - (sTmp1.length() / 2), iTopY + 1);
			cout << sTmp1;
			getline(SynopsisText, sNewReading);
			gotoxy(WIDTH - (sNewReading.length() / 2), 18);
			cout << sNewReading;
		}*/
	}
	else
	{
		ChangeColor(COLOR_RED);
		gotoxy(40, 17);
		cout << "에러: 시놉시스 파일이 없음";
	}
}

void Play::CleaningSynopsisArea()
{
	for (int y = 8; y < 19; y++)
	{
		for (int x = 15; x < 50; x++)
		{
			gotoxy(x * 2, y);
			cout << "  ";
		}
	}
}

Play::~Play()
{

}