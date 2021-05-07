#include "CardOrdering.h"


void CardOrdering::InitCard()
{
	//여기서 카드 인자를 2번씩 랜덤으로 벡터에 넣는 함수를 짜야 한다
	//카드 그림 넘버링을 짤 뿐만이 아니라 IsRevealed도 false로 초기화
	//숫자를 랜덤으로 넣는 걸 감지하는 것은 어떻게 로직을 짤 것인가->무식하지만 가장 간단한 방법으로 하기로 함

	int NumberingOne = 0, NumberingTwo = 0, NumberingThree = 0, NumberingFour = 0, NumberingFive = 0;

	m_CardVector.clear();	//벡터 비우기

	for (int i = 0; i < CARD_MAX; i++)
	{
		CardInformation NewCardInformation;
		NewCardInformation.IsRevealed = false;

		bool WhileLoop = true;	//아래 while문을 탈출시키기 위함...

		while (WhileLoop)
		{
			int RandomNumber = rand() % 5;

			switch (RandomNumber)
			{
			case 0:
				if (NumberingOne != 2)
				{
					NewCardInformation.CardNumbering = CARD_PICTURE_FIRST;
					NumberingOne++;
					WhileLoop = false;
				}
				break;
			case 1:
				if (NumberingTwo != 2)
				{
					NewCardInformation.CardNumbering = CARD_PICTURE_SECOND;
					NumberingTwo++;
					WhileLoop = false;
				}
				break;
			case 2:
				if (NumberingThree != 2)
				{
					NewCardInformation.CardNumbering = CARD_PICTURE_THIRD;
					NumberingThree++;
					WhileLoop = false;
				}
				break;
			case 3:
				if (NumberingFour != 2)
				{
					NewCardInformation.CardNumbering = CARD_PICTURE_FOURTH;
					NumberingFour++;
					WhileLoop = false;
				}
				break;
			case 4:
				if (NumberingFive != 2)
				{
					NewCardInformation.CardNumbering = CARD_PICTURE_FIFTH;
					NumberingFive++;
					WhileLoop = false;
				}
				break;
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

		m_CardVector.push_back(NewCardInformation);
	}
}

void CardOrdering::PrintCards(HDC* hdc)
{
	for (int i = 0; i < CARD_MAX; i++)
	{
		if (m_CardVector[i].IsRevealed == false)
		{
			BitMapMgr->PrintBitMap(*hdc, CARD_PICTURE_BLANK, m_CardVector[i].XLocation, m_CardVector[i].YLocation);
			
			//NewBitMapManager.PrintBitMap(*hdc, CARD_PICTURE_BLANK, m_CardVector[i].XLocation, m_CardVector[i].YLocation);
			//카드가 뒷면을 보여주고 있는 상태일 경우 공백을 넣음
		}
		else
		{
			BitMapMgr->PrintBitMap(*hdc, m_CardVector[i].CardNumbering, m_CardVector[i].XLocation, m_CardVector[i].YLocation);

			//NewBitMapManager.PrintBitMap(*hdc, m_CardVector[i].CardNumbering, m_CardVector[i].XLocation, m_CardVector[i].YLocation);
		}
	}
}

int CardOrdering::CheckOverlap(const int& MouseX, const int& MouseY)
{
	//마우스의 좌표가 카드가 있는 위치일 경우 뒤집고 해당 카드의 인덱스를 반환하는 함수

	//int i = 0;

	for (int i = 0; i < CARD_MAX; i++)
	{
		if ((MouseX >= m_CardVector.at(i).XLocation && MouseX <= (m_CardVector.at(i).XLocation + IMAGESIZE_X))
			&& (MouseY >= m_CardVector.at(i).YLocation && MouseY <= (m_CardVector.at(i).YLocation + IMAGESIZE_Y)))
		{
			if (false == m_CardVector.at(i).IsRevealed)
			{
				m_CardVector.at(i).IsRevealed = true;
				return i;
			}
		}
	}

	return NO_INDEX;
}

bool CardOrdering::IsCorrect(const int& IndexFirst, const int& IndexSecond)
{
	//뒤집어진 카드가 2개 존재할 경우 그림이 일치하는가 확인하는 함수
	if (m_CardVector[IndexFirst].CardNumbering == m_CardVector[IndexSecond].CardNumbering)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CardOrdering::CardReset(const int& IndexFirst, const int& IndexSecond)
{
	//벌칙 시간 3초가 지나면 카드를 다시 뒤집는 함수
	m_CardVector.at(IndexFirst).IsRevealed = false;
	m_CardVector.at(IndexSecond).IsRevealed = false;
}




/*
메인에서 다루던 카드 관련 함수들을 옮겨 오면서 수정 필요한 것,,,
마우스 감지해서 인덱스 없음을 어디에 반환하여 어떻게 굴려먹어야 하는가


프린트는 어케 하냐
얘가 하냐 메인이 하냐
비트맵 매니저 어디서 호출함
메인? 메인이 맞겠지

*/