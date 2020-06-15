#include "MainMenu.h"

MainMenu::MainMenu()
{
	MenuInterface.PaintWall(WIDTH, HEIGHT);
	MenuInterface.BoxDraw(0, 0, WIDTH , HEIGHT - 8);
}

void MainMenu::PrintMenu()
{
	gotoxy(30, 30);
	ChangeColor(COLOR_RED);
	cout << "테스트용";
}

MainMenu::~MainMenu()
{

}