#include <windows.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <string>

#include "BitMapManager.h"
#include "GameManager.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("C7No1");

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

	while (true)
	{
		if (PeekMessage(&Message, NULL, 0U, 0U, PM_REMOVE))
		{
			if (WM_QUIT == Message.message)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			//�׸���� �̺�Ʈ ó���Ϸ�,,,

		}
	}
	return (int)Message.wParam;
}


ULONGLONG frameTime, limitFrameTime = 0;

bool IsMoving = false;
int count = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static PAINTSTRUCT ps;


	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 150, NULL);	//ĳ���� ������ ������
		//SendMessage(hWnd, WM_TIMER, 1, 0);
		SetTimer(hWnd, 2, 0, NULL);	//Ű�Է� ������

		return 0;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
			break;
		case 2:
		{
			if(IsMoving)
			{
				if (GetAsyncKeyState(VK_LEFT))
				{

				}
				if (GetAsyncKeyState(VK_RIGHT))
				{

				}
				if (GetAsyncKeyState(VK_SPACE))
				{

				}

			}
		}
			break;
		}
	}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);



		EndPaint(hWnd, &ps);

		return 0;
	case WM_KEYDOWN:
	{
		//if(!IsMoving)
		//{
		////Chara->Moving(wParam);
		//Chara->ChangeDirection(wParam);
		//Chara->ChangeLocation();
		////Chara->ChangeGesture();
		////Chara->PrintCharacter(&hdc);
		//IsMoving = true;
		//count = 0;
		////InvalidateRect(hWnd, NULL, TRUE);
		//}

		/*switch (wParam)
		{
		case VK_LEFT:
			Chara->Moving(DIRECTION_LEFT);
			Chara->Moving(DIRECTION_LEFT);
			break;
		case VK_RIGHT:
			Chara->Moving(DIRECTION_RIGHT);
			Chara->Moving(DIRECTION_RIGHT);
			break;
		case VK_UP:
			Chara->Moving(DIRECTION_UP);
			Chara->Moving(DIRECTION_UP);
			break;
		case VK_DOWN:
			Chara->Moving(DIRECTION_DOWN);
			Chara->Moving(DIRECTION_DOWN);
			break;
		}*/
		
	}
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
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
���ο��� ����Ʈ��Ű�� �� �����µ���
��

��� �˾��� hdc�� �ּ� ������ �Ѱܾ� �� ������������

������ ���� ���� ����
clock() �Լ�? Ÿ�̸�?
�ϴ� Ÿ�̸ӷ� �غ�

*/