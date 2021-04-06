#include "resource.h"
#include "BitBitMap.h"
#include <windows.h>
#include <iostream>
#include <cmath>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("C5No1");

/////////////////////////////////////////////////////////////////////

enum PICTURE_COORDINATE
{
	PICTURE_GRAPE_X = 100,
	PICTURE_GRAPE_Y = 150,
	PICTURE_APPLE_X = 500,
	PICTURE_APPLE_Y = 350,
	PICTURE_TREE_X = 900,
	PICTURE_TREE_Y = 50
};

/////////////////////////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc, MemDC;
	static PAINTSTRUCT ps;

	BitBitMap NewBit;

	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		NewBit.PaintPicture(hWnd, ps, g_hInst, hdc);
		return 0;
	case WM_LBUTTONDOWN:

	return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

/*
좌클릭을 했을 때 좌표값을 받고->그 위치가 어떤 그림이 그려진 좌표 공간 내라면 메시지 박스가 발동하도록
*/
