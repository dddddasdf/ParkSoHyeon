#include <windows.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <string>

#include "BitMapManager.h"
#include "Character.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("C6No1");

#define MOVE_PIXEL 3	//한 번 이동할 때 얼마만큼 위치를 이동시킬 것인가

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
	static int Time = 0;	//시간 얼마나 흘렀나
	static char WhatTime[128];


	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		Chara->Init();
		return 0;
	case WM_TIMER:
		Chara->ChangeNeutral();
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		Chara->Standing(hdc);


		EndPaint(hWnd, &ps);

		{

		}
		return 0;
	case WM_KEYDOWN:
	{
		Chara->Moving(hdc, wParam);
		
		switch (wParam)
		{
		case VK_LEFT:

			break;
		case VK_RIGHT:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
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
최초 로딩시 정면을 바라보고 있는 스프라이트
각 방향 키보드 눌렀을 경우 그 방향으로 이동
키보드를 뗐을 때 가장 마지막으로 누른 방향을 향해 바라보고 서있는 스프라이트로
키입력 한 번마다 발 내딛고-서고 순차적으로 나와야 됨
bool 또는 int형으로 왼발 오른발을 저장할 변수 필요... 번갈아 가면서 발을 딛어야 하니까

움직일 때 값을 먼저 증가시키고 출력 함수를 호출한다

문제 발생함... 이미지를 읽어는 왔는데 출력 자체를 못하고 있음

*/