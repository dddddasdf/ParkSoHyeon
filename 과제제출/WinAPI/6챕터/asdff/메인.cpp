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
	static int Time = 0;	//시간 얼마나 흘렀나
	static char WhatTime[128];
	int MouseX, MouseY;


	switch (iMessage)
	{
	case WM_CREATE:
		CardMgr->InitCard();	//<-define 오류 왜 자꾸 나는 거임 뭐냐 이거 //왜 오류가 있었다가 없었다가 함 무궁화 꽃이 피었습니다라도 하냐
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
				std::string Tmp = "클리어 시간" + std::to_string(Time) + "초";

				if (MessageBox(hWnd, Tmp.c_str(), TEXT("클리어"), MB_OK))
					PostQuitMessage(0);
			}
		}
		return 0;
	case WM_LBUTTONDOWN:
	{
		if (!GameMgr->ReturnIsPenalty())
		{
			//틀린 상태라서 벌칙 시간 중이면 마우스 감지 자체를 안 받는다

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
		wsprintf(WhatTime, TEXT("%d초 "), Time);
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
카드 관련 함수들 분리 성공...
게임 매니저로 분리를 좀 더 해야

*/

/*
단순히 변수 확인만 하는 애들 const 참조로 교체할 것...
bitmapmanager 단일체화
종료할 때 메시지박스 안 뜬다

*/