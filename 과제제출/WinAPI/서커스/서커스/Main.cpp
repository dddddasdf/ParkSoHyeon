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

#define MOVE_PIXEL 3	//한 번 이동할 때 얼마만큼 위치를 이동시킬 것인가

/////////////////////////////////////////////////////////////////////

	/*while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}*/

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	HDC hdc;
	ULONGLONG frameTime, limitFrameTime = 0;
	ULONGLONG CharacterFrame = 0;

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


	hdc = GetDC(hWnd);
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

			{
				//그리기 파트
				
				GameMgr->DrawCharacterOrder(&hdc, hWnd);
				
				frameTime = GetTickCount64();       //윈도우가 시작된 후 지금까지 시간. 1/1000초.
				if (!(limitFrameTime > frameTime))  //0.03초마다 업데이트.
				{
					ULONGLONG elapsed = frameTime - limitFrameTime; //유저의 시스템 환경에 따라 발생하는 시간차이.
					limitFrameTime = frameTime + 30;//30 => 0.03초.

					CharacterFrame += elapsed;
					if (300 <= CharacterFrame)
					{
						if (GameMgr->ReturnIsMoving())
						{
							GameMgr->StandingCharacter();
						}
						CharacterFrame = 0;
					}
				}
			}
			

		}
	}
	ReleaseDC(hWnd, hdc);
	return (int)Message.wParam;
}

ULONGLONG frameTime, limitFrameTime = 0;

int count = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static PAINTSTRUCT ps;


	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 60, NULL);	//캐릭터 프레임 조절용
		//SendMessage(hWnd, WM_TIMER, 1, 0);
		SetTimer(hWnd, 2, 60, NULL);	//키입력 감지용
		//SetTimer(hWnd, 3, 1000, NULL);	//캐릭터 점프 감지용-쓸 수도 있고 아닐 수도 있고...
		GameMgr->WholeInit();	//전체 초기화
		return 0;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
		{
			if (!GameMgr->ReturnIsMoving())
			{
				if (GetAsyncKeyState(VK_LEFT) & 0x8000)
				{
					GameMgr->MovingCharacter(VK_LEFT);
				}
				if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
				{
					GameMgr->MovingCharacter(VK_RIGHT);
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
	//case WM_PAINT:
	//	hdc = BeginPaint(hWnd, &ps);

	//	GameMgr->DrawCharacterOrder(&hdc, hWnd);

	//	EndPaint(hWnd, &ps);

	//	return 0;
	//case WM_KEYDOWN:
	//{
	//	//if(!IsMoving)
	//	//{
	//	////Chara->Moving(wParam);
	//	//Chara->ChangeDirection(wParam);
	//	//Chara->ChangeLocation();
	//	////Chara->ChangeGesture();
	//	////Chara->PrintCharacter(&hdc);
	//	//IsMoving = true;
	//	//count = 0;
	//	////InvalidateRect(hWnd, NULL, TRUE);
	//	//}

	//	/*switch (wParam)
	//	{
	//	case VK_LEFT:
	//		Chara->Moving(DIRECTION_LEFT);
	//		Chara->Moving(DIRECTION_LEFT);
	//		break;
	//	case VK_RIGHT:
	//		Chara->Moving(DIRECTION_RIGHT);
	//		Chara->Moving(DIRECTION_RIGHT);
	//		break;
	//	case VK_UP:
	//		Chara->Moving(DIRECTION_UP);
	//		Chara->Moving(DIRECTION_UP);
	//		break;
	//	case VK_DOWN:
	//		Chara->Moving(DIRECTION_DOWN);
	//		Chara->Moving(DIRECTION_DOWN);
	//		break;
	//	}*/
	//	
	//}
	//	return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}



/*
시작하고 1~2초 지나면 키입력해도 안 됨
뭐가 문젠지 모르겠다...


*/