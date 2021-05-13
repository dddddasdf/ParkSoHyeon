#pragma once
#include<Windows.h>
class BitMap
{
private:
	HDC		MemDC;
	HBITMAP m_pBitMap;
	HBITMAP m_pBitOld;
	SIZE	m_size;
public:
	BitMap();
	void Init(HDC hdc, HINSTANCE hInst, int id);
	void Draw(HDC hdc, int x, int y);
	inline SIZE GetSize()
	{
		return m_size;
	}
	~BitMap();
};

