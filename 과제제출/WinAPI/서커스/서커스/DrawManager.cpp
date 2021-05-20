#include "DrawManager.h"

#define TEST_LOCATION 500	//�׽�Ʈ�� �� �ӽ� ��ǥ

void DrawManager::DrawImages(HDC hdc, int MotionNumber, int YLocation)
{
	//�� ȭ��
	HBITMAP OldBitMapFront;
	HBITMAP BitMapFront = NULL;
	HDC MemDCFront = CreateCompatibleDC(hdc);
	OldBitMapFront = (HBITMAP)SelectObject(MemDCFront, BitMapFront);

	//��� ���
	HBITMAP OlbBitMapBackground;
	HBITMAP BitMapBackground = NULL;
	HDC MemDCBackground = CreateCompatibleDC(hdc);

	//ĳ���� ���
	HBITMAP OlbBitMapCharacter;
	HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
	BITMAP BitMapCharacterSize;	//�̹��� ���� ũ�⸦ ���ϱ� ���� ��Ʈ��
	HDC MemDCCharacter = CreateCompatibleDC(hdc);

	


	//ĳ���� �׸��� ��Ʈ
	GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapCharacterSize);
	int CharacterSizeX = BitMapCharacterSize.bmWidth;
	int CharacterSizeY = BitMapCharacterSize.bmHeight;

	TransparentBlt(MemDCFront, CHARACTER_LOCATION_X, YLocation, CharacterSizeX, CharacterSizeY, MemDCCharacter, 0, 0, CharacterSizeX, CharacterSizeY, RGB(255, 0, 255));
	//ĳ���� �׸��� ��Ʈ ��


	BitBlt(hdc, 0, 0, 1024, 768, MemDCFront, 0, 0, SRCCOPY);	//�� ȭ�鿡 ���



	SelectObject(MemDCFront, OldBitMapFront);



	DeleteObject(BitMapFront);
	DeleteDC(MemDCFront);
	DeleteDC(MemDCBackground);
	DeleteDC(MemDCCharacter);
}