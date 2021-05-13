#pragma once
#include"Card.h"
#include"resource.h"

#define CARDMAX 10

class GameManager
{
private:
	Card m_CardList[CARDMAX];
public:
	GameManager();
	void Init(HWND hWnd, HINSTANCE hInst);
	void Draw(HDC hdc);
	void ColliderCheck(HWND hWnd, POINT point);
	~GameManager();
};

