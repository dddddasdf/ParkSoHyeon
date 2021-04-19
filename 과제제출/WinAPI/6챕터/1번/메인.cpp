#include <windows.h>
#include <iostream>
#include <cmath>
#include "BitMapManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("C6No1");

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
	static BitMapManager NewBitMapManager(hdc, g_hInst);

	switch (iMessage)
	{
	case WM_CREATE:
		NewBitMapManager.LoadNewImage("00");

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		NewBitMapManager.PrintBitMap(0, 100, 100);


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
생각해보니까 같은 그림인지 어케 판별함
비트맵 이름이라도 저장해둬야 하나 멤버 변수로???????
구조체 써서 넘버링 지정해두기??????????

다하고 나서 구조 문서화 필수
*/