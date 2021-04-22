#include <windows.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include "BitMapManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("C6No1");

#define NO_INDEX -5
#define NUMBER_OF_PAIR 5

/////////////////////////////////////////////////////////////////////

struct CardInformation
{
	bool IsRevealed;	//false이면 카드가 뒤집어져 있는 상태
	int CardNumbering;	//카드 그림 넘버링
	int XLocation;
	int YLocation;
};


/////////////////////////////////////////////////////////////////////

void InitCardOrder(std::vector<CardInformation> *CardVector);
void PrintCards(HDC* hdc, BitMapManager NewBitMapManager, std::vector<CardInformation> CardVector);
int CheckOverlap(std::vector<CardInformation>* CardVector, int MouseX, int MouseY);
bool IsCorrect(std::vector<CardInformation>* CardVector, int IndexFirst, int IndexSecond);

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
	static BitMapManager NewBitMapManager(hdc, g_hInst);
	static std::vector <CardInformation> CardVector = std::vector <CardInformation> ();
	static int NumberOfRevealed = 0;
	static int IndexFirst = NO_INDEX, IndexSecond = NO_INDEX;	//뒤집었을 때 인덱스 받아오는 용도
	static int NumberOfCorrect = 0;	//맞춘 개수
	int MouseX, MouseY;


	switch (iMessage)
	{
	case WM_CREATE:
		InitCardOrder(&CardVector);	//카드 정보를 저장할 벡터 초기화
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		PrintCards(&hdc, NewBitMapManager, CardVector);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);

		{
			int i = CheckOverlap(&CardVector, MouseX, MouseY);

			if (i != NO_INDEX)
			{
				if (NumberOfRevealed == 0)
					IndexFirst = i;
				else
					IndexSecond = i;

				NumberOfRevealed++;
			}
		}
		
		{
			//뒤집힌 카드의 개수가 2개가 되었다면 일치하는지 체크함
			if (NumberOfRevealed == 2)
			{
				if (IsCorrect(&CardVector, IndexFirst, IndexSecond))
				{
					NumberOfCorrect++;
				}
				NumberOfRevealed = 0;
				IndexFirst = NO_INDEX;
				IndexSecond = NO_INDEX;
			}
		}

		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void InitCardOrder(std::vector<CardInformation> *CardVector)
{
	//여기서 카드 인자를 2번씩 랜덤으로 벡터에 넣는 함수를 짜야 한다
	//카드 그림 넘버링을 짤 뿐만이 아니라 IsRevealed도 false로 초기화
	//숫자를 랜덤으로 넣는 걸 감지하는 것은 어떻게 로직을 짤 것인가->무식하지만 가장 간단한 방법으로 하기로 함

	int NumberingOne = 0, NumberingTwo = 0, NumberingThree = 0, NumberingFour = 0, NumberingFive = 0;

	int i = 0;
	
	for (int i = 0; i < 10; i++)
	{
		CardInformation NewCardInformation;
		NewCardInformation.IsRevealed = false;

		while (1)
		{
			int RandomNumber = rand() % 5;

			if (RandomNumber == 0)
			{
				if (NumberingOne != 2)
				{
					NewCardInformation.CardNumbering = CARD_PICTURE_FIRST;
					NumberingOne++;

					break;
				}
			}
			else if (RandomNumber == 1)
			{
				if (NumberingTwo != 2)
				{
					NewCardInformation.CardNumbering = CARD_PICTURE_SECOND;
					NumberingTwo++;

					break;
				}
			} 
			else if (RandomNumber == 2)
			{
				if (NumberingThree != 2)
				{
					NewCardInformation.CardNumbering = CARD_PICTURE_THIRD;
					NumberingThree++;

					break;
				}
			}
			else if (RandomNumber == 3)
			{
				if (NumberingFour != 2)
				{
					NewCardInformation.CardNumbering = CARD_PICTURE_FOURTH;
					NumberingFour++;

					break;
				}
			}
			else if (RandomNumber == 4)
			{
				if (NumberingFive != 2)
				{
					NewCardInformation.CardNumbering = CARD_PICTURE_FIFTH;
					NumberingFive++;

					break;
				}
			}
		}

		switch (i)
		{
		case 0:
			NewCardInformation.XLocation = CARD_LOCATION_FIRST_X;
			NewCardInformation.YLocation = CARD_LOCATION_FIRST_Y;
			break;
		case 1:
			NewCardInformation.XLocation = CARD_LOCATION_SECOND_X;
			NewCardInformation.YLocation = CARD_LOCATION_SECOND_Y;
			break;
		case 2:
			NewCardInformation.XLocation = CARD_LOCATION_THIRD_X;
			NewCardInformation.YLocation = CARD_LOCATION_THIRD_Y;
			break;
		case 3:
			NewCardInformation.XLocation = CARD_LOCATION_FOURTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_FOURTH_Y;
			break;
		case 4:
			NewCardInformation.XLocation = CARD_LOCATION_FIFTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_FIFTH_Y;
			break;
		case 5:
			NewCardInformation.XLocation = CARD_LOCATION_SIXTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_SIXTH_Y;
			break;
		case 6:
			NewCardInformation.XLocation = CARD_LOCATION_SEVENTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_SEVENTH_Y;
			break;
		case 7:
			NewCardInformation.XLocation = CARD_LOCATION_EIGHTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_EIGHTH_Y;
			break;
		case 8:
			NewCardInformation.XLocation = CARD_LOCATION_NINETH_X;
			NewCardInformation.YLocation = CARD_LOCATION_NINETH_Y;
			break;
		case 9:
			NewCardInformation.XLocation = CARD_LOCATION_TENTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_TENTH_Y;
			break;
		}

		CardVector->push_back(NewCardInformation);
	}
}

void PrintCards(HDC* hdc, BitMapManager NewBitMapManager, std::vector<CardInformation> CardVector)
{
	for (int i = 0; i < 10; i++)
	{
		if (CardVector[i].IsRevealed == false)
		{
			NewBitMapManager.PrintBitMap(*hdc, CARD_PICTURE_BLANK, CardVector[i].XLocation, CardVector[i].YLocation);
			//카드가 뒷면을 보여주고 있는 상태일 경우 공백을 넣음
		}
		else
		{
			NewBitMapManager.PrintBitMap(*hdc, CardVector[i].CardNumbering, CardVector[i].XLocation, CardVector[i].YLocation);
		}
	}
}

int CheckOverlap(std::vector<CardInformation>* CardVector, int MouseX, int MouseY)
{
	//마우스의 좌표가 카드가 있는 위치일 경우 뒤집고 해당 카드의 인덱스를 반환하는 함수
	
	int i = 0;

	while (i < 10)
	{
		if ((MouseX >= CardVector->at(i).XLocation && MouseX <= (CardVector->at(i).XLocation + IMAGESIZE_X))
			&& (MouseY >= CardVector->at(i).YLocation && MouseY <= (CardVector->at(i).YLocation + IMAGESIZE_Y)))
		{
			CardVector->at(i).IsRevealed = true;
			return i;
		}
		i++;
	}

	return NO_INDEX;
}

bool IsCorrect(std::vector<CardInformation>* CardVector, int IndexFirst, int IndexSecond)
{
	//뒤집어진 카드가 2개 존재할 경우 그림이 일치하는가 확인하는 함수
	if (CardVector->at(IndexFirst).CardNumbering == CardVector->at(IndexSecond).CardNumbering)
	{
		return true;
	}
	else
	{
		CardVector->at(IndexFirst).IsRevealed = false;
		CardVector->at(IndexSecond).IsRevealed = false;
		
		return false;
	}
}

/*
생각해보니까 같은 그림인지 어케 판별함
비트맵 이름이라도 저장해둬야 하나 멤버 변수로???????
구조체 써서 넘버링 지정해두기??????????

다하고 나서 구조 문서화 필수
*/

/*
구조체 배열을 만들어서
구조체 안에 뒤집어졌는지 아닌지, 카드가 갖고 있는 넘버링을 달아두는 게 좋을 듯
구조체 멤버변수
bool IsRevealed = false 일 경우 뒤집어져있는 것
int CardNumbering = 0부터 4까지
int 아무튼 좌표<-출력할 때 편하게 구조체 안에다가 좌표도 박아넣는 게 편할 듯

*/

/*
유저가 카드를 클릭했을 때 좌표 감지 후 특정 카드를 클릭했다고 치면
IsRealved를 잠시 true로 바꾸어서 그림을 활성화 시킨다
짝을 맞출 경우 true 유지, 아닐 경우 다시 false

좌표 감지해서 맞는지 아닌지 로직은 어떻게 짜야 최적화가 될까

*/

/*
배운 점: static 벡터를 동일 소스의 함수의 매개변수로 써서 값을 보존하고 싶으면 포인터로 넘겨라
벡터만 그런 게 아니라 다 그렇더라...
*/


/*
해결점을 알아냈다
한 번 호출한 오브젝트는 다시 쓸 수 없다->무조건 새로 불러와야 함
즉 비트맵 벡터에 넣어둔 다음 두고두고 쓸 수는 없다는 얘기
더 나은 방법이 있겠지만 현재 내가 가능한 방법은 이미지를 출력할 때마다 새로이 가져오는 것 외에는 방법이 없음


NewBitMapManager.LoadNewImage("Blank");	<-잘 기억해둘 것

드디어 출력이 된다
*/

/*
Overlap 함수 내에서 벡터 멤버의 구조체의 멤버 변수에 접근하려면 왜 기존에 하듯이 벡터명[]이 안 되고 .at()만 되는지 모르겠음
*/

/*
이제 해야 하는 것
타이머 기능 들여와서 현재 흐른 시간 보여줌
짝을 잘못 찾은 거라면 2초간 뒤집을 수 없고 뭘 뒤집었는지 보여줌
다 하면 메시지창 뜨면서 다시 할 거냐고 물음

*/