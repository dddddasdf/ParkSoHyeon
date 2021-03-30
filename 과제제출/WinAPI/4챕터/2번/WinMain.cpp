#include<windows.h>
#include <iostream>
#include <cmath>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("C4No2");

#define CLOCK_RADIUS 150

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
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;

	static TCHAR WhatTime[128];

	static int XCentre = 320;	//중심
	static int YCentre = 250;	//중심

	double X, Y;
	static TCHAR ClockHour[3];

	//int ClockNumberX, ClockNumberY;
	double SecondX, SecondY;
	double MinuteX, MinuteY;
	double HourX, HourY;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		{
			//시계틀 그리기
			Ellipse(hdc, XCentre - (CLOCK_RADIUS + 10), YCentre - (CLOCK_RADIUS + 10), XCentre + (CLOCK_RADIUS + 10), YCentre + (CLOCK_RADIUS + 10));
			
			for (int Hour = 1; Hour <= 12; Hour++)
			{
				X = sin((Hour * 30 * 3.1416) / 180) * CLOCK_RADIUS;
				Y = cos((Hour * 30 * 3.1416) / 180) * CLOCK_RADIUS;

				wsprintf(ClockHour, TEXT("%d"), Hour);
				TextOut(hdc, (XCentre - 4) + X, (YCentre - 7) - Y, ClockHour, lstrlen(ClockHour));
			}
		}
		{
			//분시초침 그리기
			GetLocalTime(&st);

			X = sin((st.wSecond * 6 * 3.1416) / 180);
			Y = cos((st.wSecond * 6 * 3.1416) / 180);

			SecondX = sin((st.wSecond * 6 * 3.1416) / 180) * 130;
			SecondY = cos((st.wSecond * 6 * 3.1416) / 180) * 130;

			MinuteX = sin(((st.wMinute + (double)st.wSecond / 60) * 6 * 3.1416) / 180) * 115;
			MinuteY = cos(((st.wMinute + (double)st.wSecond / 60) * 6 * 3.1416) / 180) * 115;

			HourX = sin(((st.wHour % 12 + (double)st.wMinute / 60) * 30 * 3.1416) / 180) * 90;	//왜 증가를 안 해->double로 형변환 강제로 해저ㅜ야 먹히더라 안 해주면 걍 0 나옴
			HourY = cos(((st.wHour % 12 + (double)st.wMinute / 60) * 30 * 3.1416) / 180) * 90;
		
			MoveToEx(hdc, XCentre, YCentre, NULL);
			LineTo(hdc, XCentre + SecondX, YCentre - SecondY);
			
			MoveToEx(hdc, XCentre, YCentre, NULL);
			LineTo(hdc, XCentre + MinuteX, YCentre - MinuteY);

			MoveToEx(hdc, XCentre, YCentre, NULL);
			LineTo(hdc, XCentre + HourX, YCentre - HourY);
		}
		

		{
			//현재 시각은
			TextOut(hdc, 265, 450, WhatTime, lstrlen(WhatTime));
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
	{
		GetLocalTime(&st);
		if (st.wHour == 12)
			wsprintf(WhatTime, TEXT("오후  %d : %d : %d"), st.wHour, st.wMinute, st.wSecond);
		else if (st.wHour > 12)
			wsprintf(WhatTime, TEXT("오후  %d : %d : %d"), st.wHour - 12, st.wMinute, st.wSecond);
		else
			wsprintf(WhatTime, TEXT("오전  %d : %d : %d"), st.wHour, st.wMinute, st.wSecond);
	}
	InvalidateRect(hWnd, NULL, TRUE);
	return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

/*
저번에 삼각함수로 좌표 그린 거 이용하면 될 거 같은데

분침 길이: 90
시침 길이: 60
초침 길이: 120

시계 반지름: 150
*/