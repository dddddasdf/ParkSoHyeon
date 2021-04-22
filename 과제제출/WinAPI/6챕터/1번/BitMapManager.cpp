#include "BitMapManager.h"

BitMapManager::BitMapManager(HDC hdc, HINSTANCE g_hInst) : m_hInst(g_hInst)
{

}

//bool BitMapManager::LoadNewImage, (std::string FileName)
//{
//	BitMap *NewBitMap = new BitMap(FileName);
//
//	if (NewBitMap->ReturnBitMap() != NULL)
//	{
//		m_BitMapVector.push_back(NewBitMap);
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

HBITMAP BitMapManager::LoadNewImage(std::string FileName)
{
	//BitMap *NewBitMap = new BitMap(FileName);

	BitMap NewBitMap(FileName);

	if (NewBitMap.ReturnBitMap() != NULL)
	{
		return NewBitMap.ReturnBitMap();
	}
	else
	{
		return NULL;
	}
}

void BitMapManager::PrintBitMap(HDC hdc, int BitMapNumber, int xLocation, int yLocation)
{
	HBITMAP OldBitMap;
	HBITMAP BitMap = NULL;
	HDC MemDC = CreateCompatibleDC(hdc);

	//�ʿ��� �׸� �ҷ����� �κ�
	switch (BitMapNumber)
	{
	case CARD_PICTURE_BLANK:
		BitMap = LoadNewImage("Blank" );	//ī�� �޸���
		break;
	case CARD_PICTURE_FIRST:
		BitMap = LoadNewImage("00" );
		break;
	case CARD_PICTURE_SECOND:
		BitMap = LoadNewImage("01" );
		break;
	case CARD_PICTURE_THIRD:
		BitMap = LoadNewImage("02" );
		break;
	case CARD_PICTURE_FOURTH:
		BitMap = LoadNewImage("03" );
		break;
	case CARD_PICTURE_FIFTH:
		BitMap = LoadNewImage("04" );
		break;
	}

	if (BitMap != NULL)
	{
		//IsEmpty�� true�� ���� ��� �۾� �õ�...
		OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);

		BitBlt(hdc, xLocation, yLocation, IMAGESIZE_X, IMAGESIZE_Y, MemDC, 0, 0, SRCCOPY);

		SelectObject(MemDC, OldBitMap);
	}
	DeleteObject(BitMap);
	DeleteDC(MemDC);
}