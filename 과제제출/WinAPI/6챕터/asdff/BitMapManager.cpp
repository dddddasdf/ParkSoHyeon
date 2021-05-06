#include "BitMapManager.h"

BitMapManager::BitMapManager(HINSTANCE hInst) : m_hInst(hInst)
{

}


HBITMAP BitMapManager::LoadNewImage(std::string FileName)
{
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

void BitMapManager::PrintBitMap(HDC hdc, const int& BitMapNumber, const int& xLocation, const int& yLocation)
{
	HBITMAP OldBitMap;
	HBITMAP BitMap = NULL;
	HDC MemDC = CreateCompatibleDC(hdc);

	//�ʿ��� �׸� �ҷ����� �κ�
	switch (BitMapNumber)
	{
	case CARD_PICTURE_BLANK:
		BitMap = LoadNewImage("Blank");	//ī�� �޸���
		break;
	case CARD_PICTURE_FIRST:
		BitMap = LoadNewImage("00");
		break;
	case CARD_PICTURE_SECOND:
		BitMap = LoadNewImage("01");
		break;
	case CARD_PICTURE_THIRD:
		BitMap = LoadNewImage("02");
		break;
	case CARD_PICTURE_FOURTH:
		BitMap = LoadNewImage("03");
		break;
	case CARD_PICTURE_FIFTH:
		BitMap = LoadNewImage("04");
		break;
	}

	if (BitMap != NULL)
	{
		//IsEmpty�� NULL�� �ƴ� ���� ��� �۾� �õ�...
		OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);

		BitBlt(hdc, xLocation, yLocation, IMAGESIZE_X, IMAGESIZE_Y, MemDC, 0, 0, SRCCOPY);

		SelectObject(MemDC, OldBitMap);
	}
	DeleteObject(BitMap);
	DeleteDC(MemDC);
}