#include <windows.h>
#include <iostream>
#include <cmath>
#include "BitMapManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("C6No1");

/////////////////////////////////////////////////////////////////////

void RandomCardOrder(std::vector <int> CardVector);

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
	static std::vector <int> CardVector;

	switch (iMessage)
	{
	case WM_CREATE:
		//���� ���۽� �ʿ��� �̹����� ���� �ε��ص�
		NewBitMapManager.LoadNewImage("Blank");	//ī�� �޸���
		NewBitMapManager.LoadNewImage("00");
		NewBitMapManager.LoadNewImage("01");
		NewBitMapManager.LoadNewImage("02");
		NewBitMapManager.LoadNewImage("03");
		NewBitMapManager.LoadNewImage("04");
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		NewBitMapManager.PrintBitMap(hdc, 0, CARD_LOCATION_FIRST_X, CARD_LOCATION_FIRST_Y);
		NewBitMapManager.PrintBitMap(hdc, 4, CARD_LOCATION_SIXTH_X, CARD_LOCATION_SIXTH_Y);

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

void RandomCardOrder(std::vector <int> CardVector)
{
	//���⼭ ī�� ���ڸ� 2���� �������� ���Ϳ� �ִ� �Լ��� ¥�� �Ѵ�....
}

/*
�����غ��ϱ� ���� �׸����� ���� �Ǻ���
��Ʈ�� �̸��̶� �����ص־� �ϳ� ��� ������???????
����ü �Ἥ �ѹ��� �����صα�??????????

���ϰ� ���� ���� ����ȭ �ʼ�
*/