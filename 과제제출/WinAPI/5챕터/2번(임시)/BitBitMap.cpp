#include "BitBitMap.h"

void BitBitMap::PaintPicture(HWND hWnd, PAINTSTRUCT ps, HINSTANCE gInst, HDC hdc)
{
	HDC MemDC;

	HBITMAP MyBitMap, OldBitMapTmp;

	hdc = BeginPaint(hWnd, &ps);

	MemDC = CreateCompatibleDC(hdc);

	MyBitMap = LoadBitmap(gInst, MAKEINTRESOURCE(IDB_BITMAP1));
	OldBitMapTmp = (HBITMAP)SelectObject(MemDC, MyBitMap);

	BitBlt(hdc, 100, 100, 500, 500, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitMapTmp);

	DeleteObject(MyBitMap);
	DeleteDC(MemDC);

	EndPaint(hWnd, &ps);
}