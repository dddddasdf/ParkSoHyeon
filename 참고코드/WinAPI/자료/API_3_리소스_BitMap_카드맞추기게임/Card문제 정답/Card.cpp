#include "Card.h"



Card::Card()
{
}


void Card::Init(HDC hdc, HINSTANCE hInst, int id, std::string Name, int x, int y)
{
	m_pBitMap.Init(hdc, hInst, id);
	m_ix = x;
	m_iy = y;
	m_strName = Name;
	SIZE size = m_pBitMap.GetSize();
	m_BitMapRect.left = m_ix;
	m_BitMapRect.top = m_iy;
	m_BitMapRect.right = m_BitMapRect.left + size.cx;
	m_BitMapRect.bottom = m_BitMapRect.top + size.cy;
}
void Card::Draw(HDC hdc)
{
	m_pBitMap.Draw(hdc, m_ix, m_iy);
}

void Card::ColliderCheck(HWND hWnd,POINT point)
{
	if (PtInRect(&m_BitMapRect, point))
		MessageBox(hWnd, m_strName.c_str(), m_strName.c_str(), MB_OK);
}

Card::~Card()
{
}
