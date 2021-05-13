#pragma once
#include"BitMap.h"
#include<string>
class Card
{
private:
	BitMap m_pBitMap;
	int m_ix;
	int m_iy;
	std::string m_strName;
	RECT m_BitMapRect;
public:
	Card();
	void Init(HDC hdc, HINSTANCE hInst, int id,std::string Name,int x,int y);
	void Draw(HDC hdc);
	void ColliderCheck(HWND hWnd,POINT point);
	~Card();
};

