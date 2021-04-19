#include "BitMapManager.h"

BitMapManager::BitMapManager(HDC hdc, HINSTANCE g_hInst) : m_hdc(hdc), m_hInst(g_hInst)
{

}

bool BitMapManager::LoadNewImage(std::string FileName)
{
	BitMap *NewBitMap = new BitMap(FileName);

	if (NewBitMap->ReturnBitMap() != NULL)
	{
		m_BitMapVector.push_back(NewBitMap);
		return true;
	}
	else
	{
		return false;
	}
}

void BitMapManager::PrintBitMap(int BitMapNumber, int xLocation, int yLocation)
{
	HBITMAP OldBitMap;
	HBITMAP BitMapTmp;
	HDC MemDC = CreateCompatibleDC(m_hdc);


	BitMapTmp = m_BitMapVector[BitMapNumber]->ReturnBitMap();
	OldBitMap = (HBITMAP)SelectObject(m_MemDC, BitMapTmp);

	BitBlt(m_hdc, xLocation, yLocation, 0, 0, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitMap);

	DeleteObject(BitMapTmp);
	DeleteDC(MemDC);
}