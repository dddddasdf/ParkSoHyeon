#include "DrawManager.h"

#define TEST_LOCATION 500	//�׽�Ʈ�� �� �ӽ� ��ǥ

void DrawManager::DrawImages(HDC hdc, int MotionNumber, int YLocation)
{
	//�� ȭ��
	HBITMAP OldBitMapFront;
	HBITMAP BitMapFront = NULL;
	HDC MemDCFront = CreateCompatibleDC(hdc);
	

	//��� ���
	/*HBITMAP OlbBitMapBackground;
	HBITMAP BitMapBackground = NULL;
	HDC MemDCBackground = CreateCompatibleDC(hdc);*/

	//ĳ���� ���
	HBITMAP OlbBitMapCharacter;
	HBITMAP BitMapCharacter = NULL;
	HDC MemDCCharacter = CreateCompatibleDC(hdc);
	BITMAP BitMapCharacterSize;	//�̹��� ���� ũ�⸦ ���ϱ� ���� ��Ʈ��



	//ĳ���� �׸��� ��Ʈ
	BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
	OlbBitMapCharacter = (HBITMAP)SelectObject(MemDCCharacter, BitMapCharacter);
	
	GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapCharacterSize);
	int CharacterSizeX = BitMapCharacterSize.bmWidth;
	int CharacterSizeY = BitMapCharacterSize.bmHeight;

	

	TransparentBlt(MemDCFront, CHARACTER_LOCATION_X, YLocation, CharacterSizeX, CharacterSizeY, MemDCCharacter, 0, 0, CharacterSizeX, CharacterSizeY, RGB(255, 0, 255));
	//ĳ���� �׸��� ��Ʈ ��

	OldBitMapFront = (HBITMAP)SelectObject(MemDCFront, BitMapFront);

	BitBlt(hdc, 0, 0, 1024, 768, MemDCFront, 0, 0, SRCCOPY);	//�� ȭ�鿡 ���

	SelectObject(MemDCFront, OldBitMapFront);

	//DeleteObject(BitMapFront);
	DeleteDC(MemDCFront);
	//DeleteDC(MemDCBackground);
	DeleteDC(MemDCCharacter);


	//HBITMAP OldBitMap;
	//HBITMAP BitMap = NULL;
	//HDC MemDC = CreateCompatibleDC(hdc);
	//BITMAP BitMapCharacterSize;	//�̹��� ���� ũ�⸦ ���ϱ� ���� ��Ʈ��
	//

	////�ʿ��� �׸� �ҷ����� �κ�
	//BitMap = ResourceMgr->ReturnCharacterImage(MotionNumber);
	//GetObject(BitMap, sizeof(BITMAP), &BitMapCharacterSize);

	//if (BitMap == NULL)
	//{
	//	//IsEmpty�� NULL�� �ƴ� ���� ��� �۾� �õ�... NULL�̸� return���� ���ư���

	//	DeleteObject(BitMap);
	//	DeleteDC(MemDC);

	//	return;
	//}

	//OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);

	//int CharacterSizeX = BitMapCharacterSize.bmWidth;
	//int CharacterSizeY = BitMapCharacterSize.bmHeight;

	//TransparentBlt(hdc, CHARACTER_LOCATION_X, YLocation, CharacterSizeX, CharacterSizeY, MemDC, 0, 0, CharacterSizeX, CharacterSizeY, RGB(255, 0, 255));

	//SelectObject(MemDC, OldBitMap);
	//DeleteDC(MemDC);
}