#include "MapDraw.h"


MapDraw::MapDraw()
{

}

void MapDraw::PaintWall(int Width, int Height)
{
	ChangeColor(COLOR_DARL_GRAY);
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			gotoxy(x * 2, y);
			cout << "  ";
		}
	}
	ORIGINAL
}

void MapDraw::DrawBottomBar(int x, int y)
{
	ChangeColor(COLOR_BLUE_GREEN);
	gotoxy(x, y);
	for (int x = 0; x < WIDTH * 2; x++)
		cout << "─";
	ORIGINAL
}

void MapDraw::ErasePoint(int x, int y)
{
	ChangeColor(COLOR_DARL_GRAY);
	gotoxy(x * 2, y);
	cout << "  ";
	gotoxy(-1, -1);
	ORIGINAL
	return;
}
void MapDraw::DrawPoint(string str, int x, int y)
{
	ChangeColor(COLOR_RED);
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	ORIGINAL
	return;
}

void MapDraw::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}

void MapDraw::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}

void MapDraw::BoxErase(int Width, int Height)
{
	for (int y = 1; y < Height - 1; y++)
	{
		gotoxy(2, y);
		for (int x = 1; x < Width - 1; x++)
			cout << "  ";
	}
}

void MapDraw::CleaningTop()
{
	ChangeColor(COLOR_DARL_GRAY);
	for (int y = 0; y < HORIZON; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			gotoxy(x * 2, y);
			cout << "  ";
		}
	}
	ORIGINAL
}

void MapDraw::CleaningBottom()
{
	ChangeColor(COLOR_DARL_GRAY);
	for (int y = HORIZON + 1; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			gotoxy(x * 2, y);
			cout << "  ";
		}
	}
	ORIGINAL
}

void MapDraw::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	if (Start_x > Width)
		Start_x -= Width;
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			ChangeColor(COLOR_BLUE_GREEN);
			cout << "┌";
			for (int x = 1; x < (Width * 2) - 3 ; x++)
				cout << "─";
			cout << "┐";
			ORIGINAL
		}
		else if (y == Height - 1)
		{
			ChangeColor(COLOR_BLUE_GREEN);
			cout << "└";
			for (int x = 1; x < Width - 1; x++)
				cout << "─";
			cout << "┘";
			ORIGINAL
		}
		else
		{
			ChangeColor(COLOR_BLUE_GREEN);
			cout << "│";
			for (int x = 1; x < Width; x++)
				cout << "  ";
			cout << "│";
			ORIGINAL
		}
	}
	return;
}

int MapDraw::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	int Select = 1;
	DrawPoint("▷", x, y);

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
				DrawPoint("▷", x, y);
		}
}
MapDraw::~MapDraw()
{
}
