#pragma once
#include"Headers.h"


class MapDraw
{
public:
	void PaintWall(int Width, int Height);
	void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	void BoxErase(int Width, int Height);
	void CleaningTop();
	void CleaningBottom();
	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void DrawBottomBar(int x, int y);
	void TextDraw(string str, int x, int y);
	void ErasePoint(int x, int y);
	int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);

	MapDraw();

	~MapDraw();
};