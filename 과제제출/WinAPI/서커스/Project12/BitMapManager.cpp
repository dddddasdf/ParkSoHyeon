//#include "BitMapManager.h"
//#include "Definition.h"
//
//BitMapManager::BitMapManager()
//{
//
//}
//
//
//HBITMAP BitMapManager::LoadNewImage()
//{
//	BitMap NewBitMap;
//
//	if (NewBitMap.ReturnBitMap() != NULL)
//	{
//		return NewBitMap.ReturnBitMap();
//	}
//	else
//	{
//		return NULL;
//	}
//}
//
////void BitMapManager::PrintBitMap(HDC hdc, const int& BitMapNumber, const int& xLocation, const int& yLocation)
////{
////	//HBITMAP OldBitMap;
////	//HBITMAP BitMap = NULL;
////	//HDC MemDC = CreateCompatibleDC(hdc);
////
////	////필요한 그림 불러오는 부분
////	//BitMap = LoadNewImage();
////
////	//if (BitMap != NULL)
////	//{
////	//	//IsEmpty가 NULL이 아닐 때만 출력 작업 시도...
////	//	OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);
////
////	//	BitBlt(hdc, xLocation, yLocation, IMAGESIZE_X, IMAGESIZE_Y, MemDC, 0, 0, SRCCOPY);
////
////	//	SelectObject(MemDC, OldBitMap);
////	//}
////	//DeleteObject(BitMap);
////	//DeleteDC(MemDC);
////}
//
//
//void BitMapManager::PrintBitMap(HDC hdc, const int& CharacterSight, const int& CharacterGesture, const int& xLocation, const int& yLocation)
//{
//	//CharacterSight: 캐릭터가 현재 바라보고 있는 시야를 알려준다
//	//CharacterMovement: 캐릭터가 한 발을 내딛고 있는 상태인 건지 두발로 서 있는 상태인 건지를 알려준다
//
//	/*
//	받을 매개 변수
//	출력할 비트맵 좌표
//	*/
//	
//	HBITMAP OldBitMap;
//	HBITMAP BitMap = NULL;
//	HDC MemDC = CreateCompatibleDC(hdc);
//
//	HBITMAP OlbBitMapSub;
//	HBITMAP BitMapSub = NULL;
//	HDC MemDCSub = CreateCompatibleDC(hdc);
//
//	//필요한 그림 불러오는 부분
//	//BitMap = LoadNewImage();
//	BitMapSub = LoadNewImage();
//	OlbBitMapSub = (HBITMAP)SelectObject(MemDCSub, BitMapSub);
//
//
//	/*m_BitMap[1] = LoadNewImage();
//	m_OldBitMap[1] = (HBITMAP)SelectObject(m_MemDC[1], m_BitMap[1]);*/
//
//	if (BitMapSub == NULL)
//	{
//		//IsEmpty가 NULL이 아닐 때만 출력 작업 시도... NULL이면 return으로 돌아간다
//
//		DeleteObject(BitMap);
//		DeleteDC(MemDC);
//		DeleteObject(BitMapSub);
//		DeleteDC(MemDCSub);
//
//		return;
//	}
//
//	OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);
//
//	int CutImageSizeX = IMAGE_SIZE_X / 4;
//	int CutImageSizeY = IMAGE_SIZE_Y / 4;
//
//	TransparentBlt(hdc, xLocation, yLocation, CutImageSizeX, CutImageSizeY, MemDCSub, (CutImageSizeX * CharacterGesture), (CutImageSizeY * CharacterSight), CutImageSizeX, CutImageSizeY, RGB(255, 0, 255));
//
//	BitBlt(hdc, 0, 0, 1024, 768, MemDC, 0, 0, SRCCOPY);
//
//
//	
//	SelectObject(MemDC, OldBitMap);
//
//
//
//	DeleteObject(BitMap);
//	DeleteDC(MemDC);
//	DeleteObject(BitMapSub);
//	DeleteDC(MemDCSub);
//}
//
//
//
///*
//	저렇게 하니까 너무 복잡하다
//	그냥 캐릭터가 바라보는 시야와 중립1 중립2 왼발 오른발로 쪼개서 연산시키는 게 더 나을 듯 하다
//
//	해결
//
//*/