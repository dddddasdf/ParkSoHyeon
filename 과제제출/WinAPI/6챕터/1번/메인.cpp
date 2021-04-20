#include <windows.h>
#include <iostream>
#include <cmath>
#include "BitMapManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("C6No1");

/////////////////////////////////////////////////////////////////////

void RandomCardOrder(std::vector <int> CardVector);

/////////////////////////////////////////////////////////////////////

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
	static HDC hdc, MemDC;
	static PAINTSTRUCT ps;
	static BitMapManager NewBitMapManager(hdc, g_hInst);
	static std::vector <int> CardVector;

	switch (iMessage)
	{
	case WM_CREATE:
		//최초 시작시 필요한 이미지를 전부 로드해둠
		NewBitMapManager.LoadNewImage("Blank");	//카드 뒷면임
		NewBitMapManager.LoadNewImage("00");
		NewBitMapManager.LoadNewImage("01");
		NewBitMapManager.LoadNewImage("02");
		NewBitMapManager.LoadNewImage("03");
		NewBitMapManager.LoadNewImage("04");
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		NewBitMapManager.PrintBitMap(hdc, 0, CARD_LOCATION_FIRST_X, CARD_LOCATION_FIRST_Y);
		NewBitMapManager.PrintBitMap(hdc, 4, CARD_LOCATION_SIXTH_X, CARD_LOCATION_SIXTH_Y);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void RandomCardOrder(std::vector <int> CardVector)
{
	//여기서 카드 인자를 2번씩 랜덤으로 벡터에 넣는 함수를 짜야 한다....
}

/*
생각해보니까 같은 그림인지 어케 판별함
비트맵 이름이라도 저장해둬야 하나 멤버 변수로???????
구조체 써서 넘버링 지정해두기??????????

다하고 나서 구조 문서화 필수
*/