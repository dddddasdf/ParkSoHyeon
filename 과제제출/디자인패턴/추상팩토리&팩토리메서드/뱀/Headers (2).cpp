#include "Headers (2).h"

void ChangeColor(int Color)
{
	SetConsoleTextAttribute(col, (Color + 0));
}

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}