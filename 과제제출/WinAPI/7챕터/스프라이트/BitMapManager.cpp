#include "BitMapManager.h"

BitMapManager::BitMapManager()
{

}


HBITMAP BitMapManager::LoadNewImage()
{
	BitMap NewBitMap;

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
	//HBITMAP OldBitMap;
	//HBITMAP BitMap = NULL;
	//HDC MemDC = CreateCompatibleDC(hdc);

	////�ʿ��� �׸� �ҷ����� �κ�
	//BitMap = LoadNewImage();

	//if (BitMap != NULL)
	//{
	//	//IsEmpty�� NULL�� �ƴ� ���� ��� �۾� �õ�...
	//	OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);

	//	BitBlt(hdc, xLocation, yLocation, IMAGESIZE_X, IMAGESIZE_Y, MemDC, 0, 0, SRCCOPY);

	//	SelectObject(MemDC, OldBitMap);
	//}
	//DeleteObject(BitMap);
	//DeleteDC(MemDC);
}


void BitMapManager::PrintCharacter(HDC hdc, const int& CharacterSight, const int& CharacterMovement, const int& xLocation, const int& yLocation)
{
	//CharacterSight: ĳ���Ͱ� ���� �ٶ󺸰� �ִ� �þ߸� �˷��ش�
	//CharacterMovement: ĳ���Ͱ� �� ���� ����� �ִ� ������ ���� �ι߷� �� �ִ� ������ ������ �˷��ش�
	
	HBITMAP OldBitMap;
	HBITMAP BitMap = NULL;
	HDC MemDC = CreateCompatibleDC(hdc);

	//�ʿ��� �׸� �ҷ����� �κ�
	BitMap = LoadNewImage();

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