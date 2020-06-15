#include "Headers.h"

void ChangeColor(int Color)
{
	SetConsoleTextAttribute(col, (Color + COLOR_BACKGROUND_GRAY));
}

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}