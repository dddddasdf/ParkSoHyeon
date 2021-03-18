#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <ctime>
#include <conio.h>
#include <crtdbg.h>

#define WIDTH 20
#define HEIGHT 20


enum KEYBOARD
{
	KEYBOARD_BACKSPACE = 8,
	KEYBOARD_ENTER = 13,
	KEYBOARD_UP = 72,
	KEYBOARD_DOWN = 80,
};	//엔터 상하 스페이스 입력


//////////////////////////////////////////////////////

#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );

enum COLOR
{
	COLOR_BLACK = 0,
	COLOR_DARK_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_BLUE_GREEN = 3,
	COLOR_BLOOD = 4,
	COLOR_PUPPLE = 5,
	COLOR_GOLD = 6,
	COLOR_LIGHT_GRAY = 7,
	COLOR_DARL_GRAY = 8,
	COLOR_BLUE = 9,
	COLOR_HIGH_GREEN = 10,
	COLOR_SKY_BLUE = 11,
	COLOR_RED = 12,
	COLOR_PLUM = 13,
	COLOR_YELLOW = 14,
	COLOR_BACKGROUND_GRAY = 128
};

void ChangeColor(int Color);	//폰트 색상 바꿈, 배경색은 다크 그레이 고정

//////////////////////////////////////////////////////

void gotoxy(int x, int y);

//////////////////////////////////////////////////////

