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

#define MOVE_PIXEL 3	//�� �� �̵��� �� �󸶸�ŭ ��ġ�� �̵���ų ���ΰ�

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
	static int Time = 0;	//�ð� �󸶳� �귶��
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
���� �ε��� ������ �ٶ󺸰� �ִ� ��������Ʈ
�� ���� Ű���� ������ ��� �� �������� �̵�
Ű���带 ���� �� ���� ���������� ���� ������ ���� �ٶ󺸰� ���ִ� ��������Ʈ��
Ű�Է� �� ������ �� �����-���� ���������� ���;� ��
bool �Ǵ� int������ �޹� �������� ������ ���� �ʿ�... ������ ���鼭 ���� ���� �ϴϱ�

������ �� ���� ���� ������Ű�� ��� �Լ��� ȣ���Ѵ�

���� �߻���... �̹����� �о�� �Դµ� ��� ��ü�� ���ϰ� ����

*/