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
		cout << "Ÿ�� ����";

		gotoxy(59, 15);
		cout << "1. ���� ����";

		gotoxy(59, 18);
		cout << "2. ��ŷ ����";
		
		gotoxy(59, 21);
		cout << "3. ���� ����";

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