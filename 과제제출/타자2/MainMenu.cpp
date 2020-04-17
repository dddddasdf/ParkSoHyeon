#include "MainMenu.h"

MainMenu::MainMenu()
{
	MenuInterface.DrawBottomBar(0, HORIZON);
}

void MainMenu::PrintMenu()
{
	int iSelect;

	while (1)
	{
		MenuInterface.CleaningTop();
		//MenuInterface.CleaningBottom();

		ChangeColor(COLOR_BLUE);
		gotoxy(61, 8);
		cout << "타자 게임";

		gotoxy(59, 15);
		cout << "1. 게임 시작";

		gotoxy(59, 18);
		cout << "2. 랭킹 보기";
		
		gotoxy(59, 21);
		cout << "3. 게임 종료";

		iSelect = MenuInterface.MenuSelectCursor(3, 3, 27, 15);

		switch (iSelect)
		{
		case 1:
			NowPlaying.PlayMain();
		case 3:
			return;
		}
	}
}

MainMenu::~MainMenu()
{

}