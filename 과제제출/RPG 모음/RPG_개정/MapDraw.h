#pragma once
#include"Headers.h"

void BoxDraw(int Start_x, int Start_y, int Width, int Height);
void BoxErase(int Width, int Height);
void DrawPoint(string str, int x, int y);
void DrawMidText(string str, int x, int y);
void TextDraw(string str, int x, int y);
void ErasePoint(int x, int y);
int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);