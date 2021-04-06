#include "resource.h"
#include<windows.h>
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
	HDC hdc, MemDC;
	PAINTSTRUCT ps;
	HBITMAP MyBitMap, OldBitMap;
	BITMAP BitMapTmp;

	static int xCoordinate, yCoordinate;

	static int SizeGrapeX = 0, SizeGrapeY = 0;
	static int SizeAppleX = 0, SizeAppleY = 0;
	static int SizeTreeX = 0, SizeTreeY = 0;

	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		MemDC = CreateCompatibleDC(hdc);

		//나무
		{
			MyBitMap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
			OldBitMap = (HBITMAP)SelectObject(MemDC, MyBitMap);

			if (SizeTreeX == 0)
			{
				GetObject(MyBitMap, sizeof(BITMAP), &BitMapTmp);
				SizeTreeX = BitMapTmp.bmWidth;
				SizeTreeY = BitMapTmp.bmHeight;
			}

			BitBlt(hdc, PICTURE_TREE_X, PICTURE_TREE_Y, SizeTreeX, SizeTreeY, MemDC, 0, 0, SRCCOPY);

			SelectObject(MemDC, OldBitMap);
		}
		
		//사과
		{
			MyBitMap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
			OldBitMap = (HBITMAP)SelectObject(MemDC, MyBitMap);

			if (SizeAppleX == 0)
			{
				GetObject(MyBitMap, sizeof(BITMAP), &BitMapTmp);
				SizeAppleX = BitMapTmp.bmWidth;
				SizeAppleY = BitMapTmp.bmHeight;
			}

			BitBlt(hdc, PICTURE_APPLE_X, PICTURE_APPLE_Y, SizeAppleX, SizeAppleY, MemDC, 0, 0, SRCCOPY);

			SelectObject(MemDC, OldBitMap);
		}

		//포도
		{
			MyBitMap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
			OldBitMap = (HBITMAP)SelectObject(MemDC, MyBitMap);

			if (SizeGrapeX == 0)
			{
				GetObject(MyBitMap, sizeof(BITMAP), &BitMapTmp);
				SizeGrapeX = BitMapTmp.bmWidth;
				SizeGrapeY = BitMapTmp.bmHeight;
			}

			BitBlt(hdc, PICTURE_GRAPE_X, PICTURE_GRAPE_Y, SizeGrapeX, SizeGrapeY, MemDC, 0, 0, SRCCOPY);

			SelectObject(MemDC, OldBitMap);
		}
		DeleteObject(MyBitMap);
		DeleteDC(MemDC);
		
		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:
	{
		xCoordinate = LOWORD(lParam);
		yCoordinate = HIWORD(lParam);

		if ((xCoordinate >= PICTURE_APPLE_X && xCoordinate <= (PICTURE_APPLE_X + SizeAppleX)) && (yCoordinate >= PICTURE_APPLE_Y && yCoordinate <= (PICTURE_APPLE_Y + SizeAppleY)))
		{
			MessageBox(hWnd, TEXT("사과"), TEXT("사과"), MB_OK);
		}
		else if ((xCoordinate >= PICTURE_GRAPE_X && xCoordinate <= (PICTURE_GRAPE_X + SizeGrapeX)) && (yCoordinate >= PICTURE_GRAPE_Y && yCoordinate <= (PICTURE_GRAPE_Y + SizeGrapeY)))
		{
			MessageBox(hWnd, TEXT("포도"), TEXT("포도"), MB_OK);
		}
		else if ((xCoordinate >= PICTURE_TREE_X && xCoordinate <= (PICTURE_TREE_X + SizeTreeX)) && (yCoordinate >= PICTURE_TREE_Y && yCoordinate <= (PICTURE_TREE_Y + SizeTreeY)))
		{
			MessageBox(hWnd, TEXT("나무"), TEXT("나무"), MB_OK);
		}
	}
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
