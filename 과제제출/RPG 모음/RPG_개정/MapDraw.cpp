#include "MapDraw.h"

void ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  ";
	gotoxy(-1, -1);
	return;
}
void DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	return;
}

void DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}

void TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}

void BoxErase(int Width, int Height)
{
	for (int y = 1; y < Height - 1; y++)
	{
		gotoxy(2, y);
		for (int x = 1; x < Width - 1; x++)
			cout << "  ";
	}
}

void BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	if (Start_x > Width)
		Start_x -= Width;
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			ChangeColor(COLOR_BLUE);
				cout << "┌";
			for (int x = 1; x < Width - 1; x++)
				cout << "─";
			cout << "┐";
			ORIGINAL
		}
		else if (y == Height - 1)
		{
			ChangeColor(COLOR_BLUE);
				cout << "└";
			for (int x = 1; x < Width - 1; x++)
				cout << "─";
			cout << "┘";
			ORIGINAL
		}
		else
		{
			ChangeColor(COLOR_BLUE);
				cout << "│";
			for (int x = 1; x < Width + 1; x++)
				cout << "  ";
			cout << "│";
			ORIGINAL
		}
	}
	return;
}

int MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	int Select = 1;
	ChangeColor(COLOR_RED);
		DrawPoint("▷", x, y);
	ORIGINAL
		while (1)
		{
			switch (_getch())
			{
			case KEYBOARD_UP:
				if (Select - 1 >= 1)
				{
					ErasePoint(x, y);
					y -= AddCol;
					Select--;
				}
				else if (Select == 1)
				{
					ErasePoint(x, y);
					y = y + (MenuLen - 1) * AddCol;
					Select = MenuLen;
					//맨 위 메뉴를 가리키고 있을 경우 위쪽키를 누르면 가장 아래 메뉴로 소환
				}
				break;
			case KEYBOARD_DOWN:
				if (Select + 1 <= MenuLen)
				{
					ErasePoint(x, y);
					y += AddCol;
					Select++;
				}
				else if (Select == MenuLen)
				{
					ErasePoint(x, y);
					y = y - (MenuLen - 1) * AddCol;
					Select = 1;
					//맨 아래 메뉴를 가리키고 있을 경우 아래쪽키를 누르면 가장 윗 메뉴로 소환
				}
				break;
			case KEYBOARD_ENTER:
				return Select;
			}
			ChangeColor(COLOR_RED);
				DrawPoint("▷", x, y);
			ORIGINAL
		}
}