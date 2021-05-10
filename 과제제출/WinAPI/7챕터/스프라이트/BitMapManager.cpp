#include "BitMapManager.h"
#include "Definition.h"

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

//void BitMapManager::PrintBitMap(HDC hdc, const int& BitMapNumber, const int& xLocation, const int& yLocation)
//{
//	//HBITMAP OldBitMap;
//	//HBITMAP BitMap = NULL;
//	//HDC MemDC = CreateCompatibleDC(hdc);
//
//	////필요한 그림 불러오는 부분
//	//BitMap = LoadNewImage();
//
//	//if (BitMap != NULL)
//	//{
//	//	//IsEmpty가 NULL이 아닐 때만 출력 작업 시도...
//	//	OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);
//
//	//	BitBlt(hdc, xLocation, yLocation, IMAGESIZE_X, IMAGESIZE_Y, MemDC, 0, 0, SRCCOPY);
//
//	//	SelectObject(MemDC, OldBitMap);
//	//}
//	//DeleteObject(BitMap);
//	//DeleteDC(MemDC);
//}


void BitMapManager::PrintBitMap(HDC hdc, const int& CharacterSight, const int& CharacterGesture, const int& xLocation, const int& yLocation)
{
	//CharacterSight: 캐릭터가 현재 바라보고 있는 시야를 알려준다
	//CharacterMovement: 캐릭터가 한 발을 내딛고 있는 상태인 건지 두발로 서 있는 상태인 건지를 알려준다

	/*
	받을 매개 변수
	출력할 비트맵 좌표
	*/
	
	HBITMAP OldBitMap;
	HBITMAP BitMap = NULL;
	HDC MemDC = CreateCompatibleDC(hdc);

	//필요한 그림 불러오는 부분
	BitMap = LoadNewImage();

	if (BitMap == NULL)
	{
		//IsEmpty가 NULL이 아닐 때만 출력 작업 시도... NULL이면 return으로 돌아간다

		DeleteObject(BitMap);
		DeleteDC(MemDC);

		return;
	}

	OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);

	int CutImageSizeX = IMAGE_SIZE_X / 4;
	int CutImageSizeY = IMAGE_SIZE_Y / 4;

	TransparentBlt(hdc, xLocation, yLocation, CutImageSizeX, CutImageSizeY, MemDC, (CutImageSizeX * CharacterGesture), (CutImageSizeY * CharacterSight), CutImageSizeX, CutImageSizeY, RGB(255, 0, 255));

	/*switch (CharacterSight)
	{
	case GESTURE_FRONT_NEUTRAL1:
		
		break;
	case GESTURE_FRONT_LEFT:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 1, 0, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_FRONT_NEUTRAL2:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 2, 0, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_FRONT_RIGHT:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 3, 0, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_BACK_NEUTRAL1:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, 0, (IMAGE_SIZE_Y / 4) * 1, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_BACK_LEFT:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 1, (IMAGE_SIZE_Y / 4) * 1, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_BACK_NEUTRAL2:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 2, (IMAGE_SIZE_Y / 4) * 1, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_BACK_RIGHT:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 3, (IMAGE_SIZE_Y / 4) * 1, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_LEFT_NEUTRAL1:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, 0, (IMAGE_SIZE_Y / 4) * 2, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_LEFT_LEFT:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 1, (IMAGE_SIZE_Y / 4) * 2, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_LEFT_NEUTRAL2:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 2, (IMAGE_SIZE_Y / 4) * 2, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_LEFT_RIGHT:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 3, (IMAGE_SIZE_Y / 4) * 2, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_RIGHT_NEUTRAL1:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, 0, (IMAGE_SIZE_Y / 4) * 3, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_RIGHT_LEFT:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 1, (IMAGE_SIZE_Y / 4) * 3, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_RIGHT_NEUTRAL2:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 2, (IMAGE_SIZE_Y / 4) * 3, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	case GESTURE_RIGHT_RIGHT:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, (IMAGE_SIZE_X / 4) * 3, (IMAGE_SIZE_Y / 4) * 3, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
		break;
	}*/
	
	SelectObject(MemDC, OldBitMap);

	DeleteObject(BitMap);
	DeleteDC(MemDC);
}



/*
	저렇게 하니까 너무 복잡하다
	그냥 캐릭터가 바라보는 시야와 중립1 중립2 왼발 오른발로 쪼개서 연산시키는 게 더 나을 듯 하다

	해결

*/