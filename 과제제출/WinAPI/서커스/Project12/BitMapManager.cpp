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
////	////�ʿ��� �׸� �ҷ����� �κ�
////	//BitMap = LoadNewImage();
////
////	//if (BitMap != NULL)
////	//{
////	//	//IsEmpty�� NULL�� �ƴ� ���� ��� �۾� �õ�...
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
//	//CharacterSight: ĳ���Ͱ� ���� �ٶ󺸰� �ִ� �þ߸� �˷��ش�
//	//CharacterMovement: ĳ���Ͱ� �� ���� ����� �ִ� ������ ���� �ι߷� �� �ִ� ������ ������ �˷��ش�
//
//	/*
//	���� �Ű� ����
//	����� ��Ʈ�� ��ǥ
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
//	//�ʿ��� �׸� �ҷ����� �κ�
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
//		//IsEmpty�� NULL�� �ƴ� ���� ��� �۾� �õ�... NULL�̸� return���� ���ư���
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
//	������ �ϴϱ� �ʹ� �����ϴ�
//	�׳� ĳ���Ͱ� �ٶ󺸴� �þ߿� �߸�1 �߸�2 �޹� �����߷� �ɰ��� �����Ű�� �� �� ���� �� �ϴ�
//
//	�ذ�
//
//*/