#pragma once
#include "resource.h"
#include <windows.h>
#include <iostream>

class BitBitMap
{
private:
	HBITMAP m_MyBitMap;
	HDC m_MemDC;
public:
	void PaintPicture(HWND hWnd, PAINTSTRUCT ps, HINSTANCE gInst, HDC hdc);
};

