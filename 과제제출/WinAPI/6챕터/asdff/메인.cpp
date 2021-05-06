#include <windows.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <string>
#include "BitMapManager.h"
#include "CardOrdering.h"
#include "GameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("C6No1");

#define NO_INDEX -5
#define NUMBER_OF_PAIR 5
#define INCORRECT_TIME 3

/////////////////////////////////////////////////////////////////////



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	srand(unsigned(time(NULL)));

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
	static BitMapManager NewBitMapManager(g_hInst);
	static int Time = 0;	//�ð� �󸶳� �귶��
	static char WhatTime[128];
	int MouseX, MouseY;


	switch (iMessage)
	{
	case WM_CREATE:
		CardMgr->InitCard();	//<-define ���� �� �ڲ� ���� ���� ���� �̰� //�� ������ �־��ٰ� �����ٰ� �� ����ȭ ���� �Ǿ����ϴٶ� �ϳ�
		GameMgr->InitMemberVariable();
		SetTimer(hWnd, 1, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 400, 20, WhatTime, lstrlen(WhatTime));

		CardMgr->PrintCards(&hdc, NewBitMapManager);

		EndPaint(hWnd, &ps);

		{
			if (GameMgr->IsAllCorrect())
			{
				SendMessage(hWnd, WM_DESTROY, 1, 0);
				SendMessage(hWnd, WM_DESTROY, 1, 0);

				KillTimer(hWnd, 1);
				std::string Tmp = "Ŭ���� �ð�" + std::to_string(Time) + "��";

				if (MessageBox(hWnd, Tmp.c_str(), TEXT("Ŭ����"), MB_OK))
					PostQuitMessage(0);
			}
		}
		return 0;
	case WM_LBUTTONDOWN:
	{
		if (!GameMgr->ReturnIsPenalty())
		{
			//Ʋ�� ���¶� ��Ģ �ð� ���̸� ���콺 ���� ��ü�� �� �޴´�

			MouseX = LOWORD(lParam);
			MouseY = HIWORD(lParam);

			GameMgr->MouseLeftButtonAction(MouseX, MouseY);


			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	return 0;
	case WM_TIMER:
	{
		Time++;
		wsprintf(WhatTime, TEXT("%d�� "), Time);
		if (GameMgr->ReturnIsPenalty())
		{
			GameMgr->PenaltyTimeAction();

		}
	}
	InvalidateRect(hWnd, NULL, TRUE);
	return 0;
	case WM_DESTROY:
		PostQuitMessage(0); break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


/*
ī�� ���� �Լ��� �и� ����...
���� �Ŵ����� �и��� �� �� �ؾ�

*/

/*
�ܼ��� ���� Ȯ�θ� �ϴ� �ֵ� const ������ ��ü�� ��...
bitmapmanager ����üȭ
������ �� �޽����ڽ� �� ���

*/