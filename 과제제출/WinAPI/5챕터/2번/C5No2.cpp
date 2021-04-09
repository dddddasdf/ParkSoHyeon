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
	PICTURE_TREE_Y = 50,
	PICTURE_DEFAULT_X = 100,
	PICUTRE_DEFAULT_Y = 100
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
	BitBitMap Dog(IDB_BITMAP3);
	BitBitMap Mola(IDB_BITMAP4);
	BitBitMap Mola2(IDB_BITMAP5);

	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		Dog.Draw(g_hInst, hdc);
		Mola.Draw(g_hInst, hdc, PICTURE_DEFAULT_X + 100, PICUTRE_DEFAULT_Y + 100);
		Mola2.Draw(g_hInst, hdc, 600, 300, PICTURE_DEFAULT_X + 200, PICUTRE_DEFAULT_Y + 200);
		Dog.Draw(g_hInst, hdc, 700, 800, PICTURE_DEFAULT_X + 350, PICUTRE_DEFAULT_Y + 350);

		EndPaint(hWnd, &ps);
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
