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
	float DeadCounter = 0;	//사망시 시간 멈추기 제어용

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1080, 640, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	hdc = GetDC(hWnd);
	GameMgr->WholeInit(hWnd, hdc);	//전체 초기화

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
			if (GameMgr->ReturnIsDead() == false)
			{				
				GameMgr->CollisionCheck();	//충돌 체크 함수
				GameMgr->DrawCharacterOrder(&hdc, hWnd);	//그리는 함수 호출
				
				

				//여기서부터 프레임 제어 파트
				
				frameTime = GetTickCount64();       //윈도우가 시작된 후 지금까지 시간. 1/1000초.
				if (!(limitFrameTime > frameTime))  //0.03초마다 업데이트.
				{
					float elapsed = (frameTime - limitFrameTime) * 0.01f; //유저의 시스템 환경에 따라 발생하는 시간차이.
					limitFrameTime = frameTime + 30;//30 => 0.03초.

					CharacterFrame += elapsed;
					JumpCounter += elapsed;

					if (0.02f <= JumpCounter)
					{
						//점프하는 부분
						if (GameMgr->ReturnIsJumping())
						{
							GameMgr->ChangeCharacterYLocation();
						}
						JumpCounter = 0;
					}

					if (0.02f <= CharacterFrame)
					{
						//캐릭터 움직이는 부분
						/*if (GameMgr->ReturnIsMoving() && (!GameMgr->ReturnIsJumping()))
						{
							GameMgr->StandingCharacter();
						}*/
						
						if ((!GameMgr->ReturnIsJumping()))
						{
							GameMgr->StandingCharacter();
						}
						/*
						모션 교체를 위하여 메인 함수에서는 캐릭터가 점프 중이 아닐 때 모션을 갱신하도록 변경하였음
						자세한 내막은 GameManager의 StandCharacter() 함수로...
						*/
						CharacterFrame = 0;
					}

					GameMgr->CalculateRings(elapsed);	//링 위치 조절하는 곳
				}
			}
			else
			{
				frameTime = GetTickCount64();       //윈도우가 시작된 후 지금까지 시간. 1/1000초.
				if (!(limitFrameTime > frameTime))  //0.03초마다 업데이트.
				{
					float elapsed = (frameTime - limitFrameTime) * 0.01f; //유저의 시스템 환경에 따라 발생하는 시간차이.
					limitFrameTime = frameTime + 30;//30 => 0.03초.

					DeadCounter += elapsed;

					if (0.5f <= DeadCounter)
					{
						GameMgr->PartialInit();
						DeadCounter = 0;
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
		//SetTimer(hWnd, 3, 1000, NULL);	//캐릭터 점프 감지용-쓸 수도 있고 아닐 수도 있고...
		
		return 0;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
		{
			{
				//캐릭터가 움직이고 있는 중이거나 점프 중일 때는 방향키값 체크 X
				//점프는 점프 중인지만 확인한다<-이것들 싹다 게임매니저에 넣는 게 낫나?? 낫나???
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
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		DrawMgr->~DrawManager();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}



/*
시작하고 1~2초 지나면 키입력해도 안 됨
뭐가 문젠지 모르겠다...<-해결함

현재까지 구현 완료한 것
캐릭터 움직이는 모션 구현
캐릭터 점프하는 모션 구현


이제 고민해야 하는 부분
백그라운드를 어떻게 출력시킬 것인지<-해결함


맵 이동까지 구현하고 나면 이제 장애물 배치와 충돌체크를 확인하도록 하자...

맵그리기까지 다했음
이제 스크롤 기능 구현할 차례임

스크롤 기능 반쯤 구현함...
현재 해야 하는 거
1. 이동 중에 점프하면 X좌표 지속적으로 움직여주기
2. 속도감 문제

elapsed를 곱하라는데 사실 이거 뭔 말인지 모르겠음

이거 내가 로직 제대로 짜고 있는 거 맞나?/?


이제 장애물 배치가 중요함
원판에서는 동일 패턴을 사이클 돌리면서 내는 건지 아니면 처음부터 끝까지 패턴이 배치되어있는건지 아닌 건지 똥손이라 못해서 모르겠음

화로 출력까진 성공함
고리 출력시키면서 어떻게 이동시킬지가 겁나게 문젠데
일단 고리 리젠은 일정 시간마다 하는 게 편하긴 할 거 같음

유저가 불 고리의 X좌표와 겹쳐서 지나간 다음 불 고리가 화면 너머로 사라지는 순간 불고리의 존재가 말소되어버림
큰 고리는 5초마다 젠 시킨다 칩시다
작은 고리는 10초마다 젠<-못해먹겠어서 그냥 좌표별로 나오도록 함

불고리 좌표는 draw에서 관리하는 게 맞긋지...
불고리 위치가 유저 위치보다 100 아래로 가면 화면 오른쪽으로 가서 대기...

엔딩 어케 나는지를 알아야 겟는데 엔딩을 못 봐서 못구현하겟음 걍 아무렇게나 해야지

이제 충돌 구현을 해야 할 차례
이거 연산 너무 많은 거 아닌가??? 비트맵은 아예 멤버변수로 저장해버리는 게 낫나...

화로 위치 출력을 좀 바꾸는 게 낫겟음,,, 상대위치보다는 절대위치식으로<-해봣는데 뭐가 나은지 잘 모르겟음,,,,,,,

충돌체크 구현부터 하자
ㄴ돈주머니 충돌 체크 구현 완료...
ㄴ화로 충돌 체크 거의 다 됐는데...... 위치 계산 에러가 난 것 같다 이것 확인

그리고 죽었을 때 전체 초기화가 아니라 장애물과 유저 위치만 초기화 하는 반반초기화 함수 증설 필요...

반반초기화 함수 증설 완료,,, 화로 충돌 위치 버그 고쳐야 됨
ㄴ고침


CBitmap 이미지 데이터 정보, 로드된 이미지 저장
CObject CBitmap, x, y, ..., virtual Update() = 0;
CFirering : CObject
CFirering2 : CFirering
CireBottle : CObject
CPlayer : CObject, .....
CBackground : CObject,

m_ringPivot

고리랑 충돌판정 잘못 일어나는 거 지금 이유...
캐릭터 좌표는 맵길이상의 X좌표인데 고리는 화면상에서의 X좌표라서
고리 좌표를 맵길이상의 좌표로 옮겨야 할 필요성 있음

상속받은 플레이어 오브젝트는 HBITMAP 벡터를 들고있는 거롤....
오ㅓ브젝트들도 전부 벡터 갖고 있나? 애니메이션 조정하게

상속 어케함 어렵네

벡터는 만들지 못하고 배열식으로 임의로 할 수는 있을 것 같은데 아님 말고


오늘 할 우선 순위
일단 오브젝트들 상속으로 전부 완성함
그다음 고리의 좌표를 상대좌표(화면이 기준)가 아니라 절대좌표(맵이 기준)으로 수정할 것...

이렇게 되면 리소스매니저가 하는 일이 뭐지???????????????
for문 다 분리시켜야 하나??

순차적으로 옮기는 중

업데이트 함수 뭐에 쓰는 거지

고리 움직일 때 피벗 어케 쓰더라
화로는 지금 관리 방식 때문에 클래스로 옮겨야 할지 고민되는데 이거 물어봐야 할 듯 

나중에 매크로로 써도 되는 상수들도 다 빼야한다...
*/