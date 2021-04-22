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
	bool IsRevealed;	//false�̸� ī�尡 �������� �ִ� ����
	int CardNumbering;	//ī�� �׸� �ѹ���
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
	static int IndexFirst = NO_INDEX, IndexSecond = NO_INDEX;	//�������� �� �ε��� �޾ƿ��� �뵵
	static int NumberOfCorrect = 0;	//���� ����
	int MouseX, MouseY;


	switch (iMessage)
	{
	case WM_CREATE:
		InitCardOrder(&CardVector);	//ī�� ������ ������ ���� �ʱ�ȭ
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
			//������ ī���� ������ 2���� �Ǿ��ٸ� ��ġ�ϴ��� üũ��
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
	//���⼭ ī�� ���ڸ� 2���� �������� ���Ϳ� �ִ� �Լ��� ¥�� �Ѵ�
	//ī�� �׸� �ѹ����� © �Ӹ��� �ƴ϶� IsRevealed�� false�� �ʱ�ȭ
	//���ڸ� �������� �ִ� �� �����ϴ� ���� ��� ������ © ���ΰ�->���������� ���� ������ ������� �ϱ�� ��

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
			//ī�尡 �޸��� �����ְ� �ִ� ������ ��� ������ ����
		}
		else
		{
			NewBitMapManager.PrintBitMap(*hdc, CardVector[i].CardNumbering, CardVector[i].XLocation, CardVector[i].YLocation);
		}
	}
}

int CheckOverlap(std::vector<CardInformation>* CardVector, int MouseX, int MouseY)
{
	//���콺�� ��ǥ�� ī�尡 �ִ� ��ġ�� ��� ������ �ش� ī���� �ε����� ��ȯ�ϴ� �Լ�
	
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
	//�������� ī�尡 2�� ������ ��� �׸��� ��ġ�ϴ°� Ȯ���ϴ� �Լ�
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
�����غ��ϱ� ���� �׸����� ���� �Ǻ���
��Ʈ�� �̸��̶� �����ص־� �ϳ� ��� ������???????
����ü �Ἥ �ѹ��� �����صα�??????????

���ϰ� ���� ���� ����ȭ �ʼ�
*/

/*
����ü �迭�� ����
����ü �ȿ� ������������ �ƴ���, ī�尡 ���� �ִ� �ѹ����� �޾Ƶδ� �� ���� ��
����ü �������
bool IsRevealed = false �� ��� ���������ִ� ��
int CardNumbering = 0���� 4����
int �ƹ�ư ��ǥ<-����� �� ���ϰ� ����ü �ȿ��ٰ� ��ǥ�� �ھƳִ� �� ���� ��

*/

/*
������ ī�带 Ŭ������ �� ��ǥ ���� �� Ư�� ī�带 Ŭ���ߴٰ� ġ��
IsRealved�� ��� true�� �ٲپ �׸��� Ȱ��ȭ ��Ų��
¦�� ���� ��� true ����, �ƴ� ��� �ٽ� false

��ǥ �����ؼ� �´��� �ƴ��� ������ ��� ¥�� ����ȭ�� �ɱ�

*/

/*
��� ��: static ���͸� ���� �ҽ��� �Լ��� �Ű������� �Ἥ ���� �����ϰ� ������ �����ͷ� �Ѱܶ�
���͸� �׷� �� �ƴ϶� �� �׷�����...
*/


/*
�ذ����� �˾Ƴ´�
�� �� ȣ���� ������Ʈ�� �ٽ� �� �� ����->������ ���� �ҷ��;� ��
�� ��Ʈ�� ���Ϳ� �־�� ���� �ΰ�ΰ� �� ���� ���ٴ� ���
�� ���� ����� �ְ����� ���� ���� ������ ����� �̹����� ����� ������ ������ �������� �� �ܿ��� ����� ����


NewBitMapManager.LoadNewImage("Blank");	<-�� ����ص� ��

���� ����� �ȴ�
*/

/*
Overlap �Լ� ������ ���� ����� ����ü�� ��� ������ �����Ϸ��� �� ������ �ϵ��� ���͸�[]�� �� �ǰ� .at()�� �Ǵ��� �𸣰���
*/

/*
���� �ؾ� �ϴ� ��
Ÿ�̸� ��� �鿩�ͼ� ���� �帥 �ð� ������
¦�� �߸� ã�� �Ŷ�� 2�ʰ� ������ �� ���� �� ���������� ������
�� �ϸ� �޽���â �߸鼭 �ٽ� �� �ųİ� ����

*/