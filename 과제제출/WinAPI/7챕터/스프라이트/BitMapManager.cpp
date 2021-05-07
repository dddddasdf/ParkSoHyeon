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

	////필요한 그림 불러오는 부분
	//BitMap = LoadNewImage();

	//if (BitMap != NULL)
	//{
	//	//IsEmpty가 NULL이 아닐 때만 출력 작업 시도...
	//	OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);

	//	BitBlt(hdc, xLocation, yLocation, IMAGESIZE_X, IMAGESIZE_Y, MemDC, 0, 0, SRCCOPY);

	//	SelectObject(MemDC, OldBitMap);
	//}
	//DeleteObject(BitMap);
	//DeleteDC(MemDC);
}


void BitMapManager::PrintCharacter(HDC hdc, const int& CharacterSight, const int& CharacterMovement, const int& xLocation, const int& yLocation)
{
	//CharacterSight: 캐릭터가 현재 바라보고 있는 시야를 알려준다
	//CharacterMovement: 캐릭터가 한 발을 내딛고 있는 상태인 건지 두발로 서 있는 상태인 건지를 알려준다
	
	HBITMAP OldBitMap;
	HBITMAP BitMap = NULL;
	HDC MemDC = CreateCompatibleDC(hdc);

	//필요한 그림 불러오는 부분
	BitMap = LoadNewImage();

	if (BitMap != NULL)
	{
		//IsEmpty가 NULL이 아닐 때만 출력 작업 시도...
		OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);

		BitBlt(hdc, xLocation, yLocation, IMAGESIZE_X, IMAGESIZE_Y, MemDC, 0, 0, SRCCOPY);

		SelectObject(MemDC, OldBitMap);
	}
	DeleteObject(BitMap);
	DeleteDC(MemDC);
}