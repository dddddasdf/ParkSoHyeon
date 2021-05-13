#include "BitMap.h"



BitMap::BitMap()
{
}


void BitMap::Init(HDC hdc, HINSTANCE hInst, int id)
{
	MemDC = CreateCompatibleDC(hdc);
	m_pBitMap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(id));
	m_pBitOld = (HBITMAP)SelectObject(MemDC, m_pBitMap);

	BITMAP BitMap_Info;
	GetObject(m_pBitMap, sizeof(BitMap_Info), &BitMap_Info);
	m_size.cx = BitMap_Info.bmWidth;
	m_size.cy = BitMap_Info.bmHeight;
}
void BitMap::Draw(HDC hdc, int x, int y,int spX, int spY)
{
	StretchBlt(hdc, x, y, m_size.cx * spX, m_size.cy * spY, MemDC, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
}

BitMap::~BitMap()
{
	SelectObject(MemDC, m_pBitOld);
	DeleteObject(m_pBitMap);
	DeleteDC(MemDC);
}
