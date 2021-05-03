#pragma once
#include <vector>
#include "Enums.h"
#include "TemplateSingleton.h"
#include "BitMapManager.h"

struct CardInformation
{
	bool IsRevealed;	//false이면 카드가 뒤집어져 있는 상태
	int CardNumbering;	//카드 그림 넘버링
	int XLocation;
	int YLocation;
};

class CardOrdering : public Singleton <CardOrdering>
{
private:
	std::vector <CardInformation> m_CardVector;

public:
	void InitCard();
	void PrintCards(HDC* hdc, BitMapManager NewBitMapManager);
	int CheckOverlap(int MouseX, int MouseY);
	bool IsCorrect(int IndexFirst, int IndexSecond);
	void CardReset(int IndexFirst, int IndexSecond);
};

