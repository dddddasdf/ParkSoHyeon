#include "Menu.h"



Menu::Menu()
{
}

void Menu::PrintMainMenu()
{
	MenuMap.BoxDraw(0, 0, WIDTH, HEIGHT);
	

	int iSelect;

	while (1)
	{
		MenuMap.BoxErase(WIDTH, HEIGHT);

		GOLD
			gotoxy(29, 10);
		cout << "RPG";
		ORIGINAL

			gotoxy(27, 13);
		cout << "새　게임";
		gotoxy(27, 16);
		cout << "불러오기";
		gotoxy(27, 19);
		cout << "종료하기";

		iSelect = MenuMap.MenuSelectCursor(3, 3, 11, 13);

		switch (iSelect)
		{
		case 1:
			NewGame();
			break;
		case 2:
			LoadData();
			break;
		case 3:
			return;
		}
	}
}

void Menu::NewGame()
{
	MenuMap.BoxErase(WIDTH, HEIGHT);

	string sNewPlayer;
	gotoxy(15, 14);
	cout << "유저 이름 입력: ";
	cin >> sNewPlayer;

	RolePlaying.GetName(sNewPlayer);
	RolePlaying.TownMenu();
}

void Menu::LoadData()
{
	MenuMap.BoxErase(WIDTH, HEIGHT);

	int iSelect;
	for (int i = 1; i <= 10; i++)
	{
		gotoxy(20, 2 + (i * 2));
		cout << "지금은 테스트용 문장" << i;
	}
	gotoxy(27, 24);
	cout << "돌아간다";

	iSelect = MenuMap.MenuSelectCursor(11, 2, 8, 4);

	switch (iSelect)
	{
	default:
		cout << "댕";
		break;
	case 11:
		return;
	}
}


Menu::~Menu()
{
}
