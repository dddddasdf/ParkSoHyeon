#pragma once
#include <vector>
#include "Enums.h"
#include "TemplateSingleton.h"
#include "BitMapManager.h"

struct CardInformation
{
	bool IsRevealed;	//false�̸� ī�尡 �������� �ִ� ����
	int CardNumbering;	//ī�� �׸� �ѹ���
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
	int CheckOverlap(const int& MouseX, const int& MouseY);
	bool IsCorrect(const int& IndexFirst, const int& IndexSecond);
	void CardReset(const int& IndexFirst, const int& IndexSecond);
};
#define CardMgr CardOrdering::GetInstance()
