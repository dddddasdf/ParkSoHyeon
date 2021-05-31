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
	ULONGLONG frameTime, limitFrameTime = GetTickCount64();
	float CharacterFrame = 0;	//캐릭터 프레임 제어용
	float JumpCounter = 0;	//점프 프레임 제어용

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

					CharacterFrame += elapsed * 0.01f;
					JumpCounter += elapsed * 0.01f;

					if (0.02f <= JumpCounter)
					{
						//점프하는 부분
						if (GameMgr->ReturnIsJumping())
						{
							GameMgr->ChangeCharacterYLocation();
						}
						JumpCounter = 0;
					}

					if (0.05f <= CharacterFrame)
					{
						//캐릭터 움직이는 부분
						if (GameMgr->ReturnIsMoving() && (!GameMgr->ReturnIsJumping()))
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
		GameMgr->WholeInit(hWnd);	//전체 초기화
		return 0;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
		{
			//캐릭터가 움직이고 있는 중이거나 점프 중일 때는 방향키값 체크 X
			//점프는 점프 중인지만 확인한다
			{
				if (GetAsyncKeyState(VK_SPACE))
				{
					if (!GameMgr->ReturnIsJumping())
					{
						GameMgr->JumpingCharacter();
					}
				}
				if ((!GameMgr->ReturnIsMoving()) && (!GameMgr->ReturnIsJumping()))
				{
					if (GetAsyncKeyState(VK_LEFT) & 0x8000)
					{
						GameMgr->MovingCharacter(VK_LEFT);
					}
					if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
					{
						GameMgr->MovingCharacter(VK_RIGHT);
					}
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

현재까지 구현 완료한 것
캐릭터 움직이는 모션 구현
캐릭터 점프하는 모션 구현


이제 고민해야 하는 부분
백그라운드를 어떻게 출력시킬 것인지


맵 이동까지 구현하고 나면 이제 장애물 배치와 충돌체크를 확인하도록 하자...

맵그리기까지 다했음
이제 스크롤 기능 구현할 차례임

스크롤 기능 반쯤 구현함...
현재 해야 하는 거
1. 이동 중에 점프하면 X좌표 지속적으로 움직여주기
2. 속도감 문제
*/