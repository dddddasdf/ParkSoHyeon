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


void BitMapManager::PrintCharacter(HDC hdc, const int& CharacterSight, const int& xLocation, const int& yLocation)
{
	//CharacterSight: ĳ���Ͱ� ���� �ٶ󺸰� �ִ� �þ߸� �˷��ش�
	//CharacterMovement: ĳ���Ͱ� �� ���� ����� �ִ� ������ ���� �ι߷� �� �ִ� ������ ������ �˷��ش�

	/*
	���� �Ű� ����
	����� ��Ʈ�� ��ǥ
	*/
	
	HBITMAP OldBitMap;
	HBITMAP BitMap = NULL;
	HDC MemDC = CreateCompatibleDC(hdc);

	//�ʿ��� �׸� �ҷ����� �κ�
	BitMap = LoadNewImage();

	if (BitMap == NULL)
	{
		//IsEmpty�� NULL�� �ƴ� ���� ��� �۾� �õ�...

		DeleteObject(BitMap);
		DeleteDC(MemDC);

		return;
	}

	OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);

	BitBlt(hdc, xLocation, yLocation, IMAGE_SIZE_X, IMAGE_SIZE_Y, MemDC, 0, 0, SRCCOPY);

	/*switch (CharacterSight)
	{
	case GESTURE_FRONT_NEUTRAL1:
		TransparentBlt(hdc, xLocation, yLocation, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), MemDC, 0, 0, (IMAGE_SIZE_X / 4), (IMAGE_SIZE_Y / 4), RGB(255, 0, 255));
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
������ ������ ����
transperantblt���� ������,,, ���̺귯���� ������ �鿩�;� �ϴ���...
#pragma comment (lib, "Msimg32.lib")

*/