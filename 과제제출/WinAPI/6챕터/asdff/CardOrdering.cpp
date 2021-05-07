#include "CardOrdering.h"


void CardOrdering::InitCard()
{
	//���⼭ ī�� ���ڸ� 2���� �������� ���Ϳ� �ִ� �Լ��� ¥�� �Ѵ�
	//ī�� �׸� �ѹ����� © �Ӹ��� �ƴ϶� IsRevealed�� false�� �ʱ�ȭ
	//���ڸ� �������� �ִ� �� �����ϴ� ���� ��� ������ © ���ΰ�->���������� ���� ������ ������� �ϱ�� ��

	int NumberingOne = 0, NumberingTwo = 0, NumberingThree = 0, NumberingFour = 0, NumberingFive = 0;

	m_CardVector.clear();	//���� ����

	for (int i = 0; i < CARD_MAX; i++)
	{
		CardInformation NewCardInformation;
		NewCardInformation.IsRevealed = false;

		bool WhileLoop = true;	//�Ʒ� while���� Ż���Ű�� ����...

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
			//ī�尡 �޸��� �����ְ� �ִ� ������ ��� ������ ����
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
	//���콺�� ��ǥ�� ī�尡 �ִ� ��ġ�� ��� ������ �ش� ī���� �ε����� ��ȯ�ϴ� �Լ�

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
	//�������� ī�尡 2�� ������ ��� �׸��� ��ġ�ϴ°� Ȯ���ϴ� �Լ�
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
	//��Ģ �ð� 3�ʰ� ������ ī�带 �ٽ� ������ �Լ�
	m_CardVector.at(IndexFirst).IsRevealed = false;
	m_CardVector.at(IndexSecond).IsRevealed = false;
}




/*
���ο��� �ٷ�� ī�� ���� �Լ����� �Ű� ���鼭 ���� �ʿ��� ��,,,
���콺 �����ؼ� �ε��� ������ ��� ��ȯ�Ͽ� ��� �����Ծ�� �ϴ°�


����Ʈ�� ���� �ϳ�
�갡 �ϳ� ������ �ϳ�
��Ʈ�� �Ŵ��� ��� ȣ����
����? ������ �°���

*/