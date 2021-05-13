#pragma once
#include<Windows.h>
#include<string>
class BitMap
{
private:
	HDC MemDC;
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;
	SIZE m_Size;
public:
	void Init(HDC hdc, HINSTANCE hInst,char* FileName);
	void Draw(HDC hdc, int x, int y);
	BitMap();
	~BitMap();
};

