#include "BitMapManager.h"

BitMapManager::BitMapManager(HDC hdc, HINSTANCE g_hInst) : m_hInst(g_hInst)
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

void BitMapManager::PrintBitMap(HDC hdc, int BitMapNumber, int xLocation, int yLocation)
{
	HBITMAP OldBitMap;
	HBITMAP BitMapTmp;
	//BITMAP BitMapSize;	//사진 크기 구하는 용
	HDC MemDC = CreateCompatibleDC(hdc);
	//int PictureSizeX, PictureSizeY;	//사진 크기 저장할 변수

	BitMapTmp = m_BitMapVector[BitMapNumber]->ReturnBitMap();
	OldBitMap = (HBITMAP)SelectObject(MemDC, BitMapTmp);

	//사진 크기 구하는 파트
	/*GetObject(BitMapTmp, sizeof(BITMAP), &BitMapSize);
	PictureSizeX = BitMapSize.bmWidth;
	PictureSizeY = BitMapSize.bmHeight;*/
	//사진 크기 구하는 파트 종료-이번 건 안 씀 너무 복잡해질 거 같아서...

	BitBlt(hdc, xLocation, yLocation, IMAGESIZE_X, IMAGESIZE_Y, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitMap);

	DeleteObject(BitMapTmp);
	DeleteDC(MemDC);
}