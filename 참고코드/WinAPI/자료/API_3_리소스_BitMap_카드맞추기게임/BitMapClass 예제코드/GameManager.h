#pragma once
#include"resource.h"
#include"BitMap.h"
#define CARDMAX 10

class GameManager
{
private:
	BitMap m_BitMap;
	BitMap m_BitMap2;
public:
	GameManager();
	void Init(HWND hWnd, HINSTANCE hInst);
	void Draw(HDC hdc,int x,int y);
	~GameManager();
};

