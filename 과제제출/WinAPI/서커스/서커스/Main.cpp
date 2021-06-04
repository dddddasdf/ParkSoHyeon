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
	float CharacterFrame = 0;	//ĳ���� ������ �����
	float JumpCounter = 0;	//���� ������ �����

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
				GameMgr->DrawCharacterOrder(&hdc, hWnd);	//�׸��� �Լ� ȣ��

				//���⼭���� ������ ���� ��Ʈ
				
				frameTime = GetTickCount64();       //�����찡 ���۵� �� ���ݱ��� �ð�. 1/1000��.
				if (!(limitFrameTime > frameTime))  //0.03�ʸ��� ������Ʈ.
				{
					float elapsed = (frameTime - limitFrameTime) * 0.01f; //������ �ý��� ȯ�濡 ���� �߻��ϴ� �ð�����.
					limitFrameTime = frameTime + 30;//30 => 0.03��.

					CharacterFrame += elapsed;
					JumpCounter += elapsed;

					if (0.02f <= JumpCounter)
					{
						//�����ϴ� �κ�
						if (GameMgr->ReturnIsJumping())
						{
							GameMgr->ChangeCharacterYLocation();
						}
						JumpCounter = 0;
					}

					if (0.02f <= CharacterFrame)
					{
						//ĳ���� �����̴� �κ�
						/*if (GameMgr->ReturnIsMoving() && (!GameMgr->ReturnIsJumping()))
						{
							GameMgr->StandingCharacter();
						}*/
						
						if ((!GameMgr->ReturnIsJumping()))
						{
							GameMgr->StandingCharacter();
						}
						/*
						��� ��ü�� ���Ͽ� ���� �Լ������� ĳ���Ͱ� ���� ���� �ƴ� �� ����� �����ϵ��� �����Ͽ���
						�ڼ��� ������ GameManager�� StandCharacter() �Լ���...
						*/
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
		SetTimer(hWnd, 1, 60, NULL);	//ĳ���� ������ ������
		//SendMessage(hWnd, WM_TIMER, 1, 0);
		//SetTimer(hWnd, 3, 1000, NULL);	//ĳ���� ���� ������-�� ���� �ְ� �ƴ� ���� �ְ�...
		GameMgr->WholeInit(hWnd);	//��ü �ʱ�ȭ
		return 0;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
		{
			{
				//ĳ���Ͱ� �����̰� �ִ� ���̰ų� ���� ���� ���� ����Ű�� üũ X
				//������ ���� �������� Ȯ���Ѵ�<-�̰͵� �ϴ� ���ӸŴ����� �ִ� �� ����?? ����???
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
				if (GetAsyncKeyState(VK_SPACE))
				{
					if (!GameMgr->ReturnIsJumping())
					{
						GameMgr->JumpingCharacter();
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
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}



/*
�����ϰ� 1~2�� ������ Ű�Է��ص� �� ��
���� ������ �𸣰ڴ�...<-�ذ���

������� ���� �Ϸ��� ��
ĳ���� �����̴� ��� ����
ĳ���� �����ϴ� ��� ����


���� ����ؾ� �ϴ� �κ�
��׶��带 ��� ��½�ų ������<-�ذ���


�� �̵����� �����ϰ� ���� ���� ��ֹ� ��ġ�� �浹üũ�� Ȯ���ϵ��� ����...

�ʱ׸������ ������
���� ��ũ�� ��� ������ ������

��ũ�� ��� ���� ������...
���� �ؾ� �ϴ� ��
1. �̵� �߿� �����ϸ� X��ǥ ���������� �������ֱ�
2. �ӵ��� ����

elapsed�� ���϶�µ� ��� �̰� �� ������ �𸣰���

�̰� ���� ���� ����� ¥�� �ִ� �� �³�?/?


���� ��ֹ� ��ġ�� �߿���
���ǿ����� ���� ������ ����Ŭ �����鼭 ���� ���� �ƴϸ� ó������ ������ ������ ��ġ�Ǿ��ִ°��� �ƴ� ���� �˼��̶� ���ؼ� �𸣰���

ȭ�� ��±��� ������
�� ��½�Ű�鼭 ��� �̵���ų���� �̳��� ������
�ϴ� �� ������ ���� �ð����� �ϴ� �� ���ϱ� �� �� ����

������ �� ���� X��ǥ�� ���ļ� ������ ���� �� ���� ȭ�� �ʸӷ� ������� ���� �Ұ��� ���簡 ���ҵǾ����
ū ���� 5�ʸ��� �� ��Ų�� Ĩ�ô�
���� ���� 10�ʸ��� ��

�Ұ� ��ǥ�� draw���� �����ϴ� �� �±���...
�Ұ� ��ġ�� ���� ��ġ���� 100 �Ʒ��� ���� ȭ�� ���������� ���� ���...
*/