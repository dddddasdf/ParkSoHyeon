#include "DrawManager.h"

#define TEST_LOCATION 500	//테스트할 때 임시 좌표

void DrawManager::DrawImages(HDC hdc, int MotionNumber, int YLocation)
{
	//본 화면
	HBITMAP OldBitMapFront;
	HBITMAP BitMapFront = NULL;
	HDC MemDCFront = CreateCompatibleDC(hdc);
	OldBitMapFront = (HBITMAP)SelectObject(MemDCFront, BitMapFront);

	//배경 담당
	HBITMAP OlbBitMapBackground;
	HBITMAP BitMapBackground = NULL;
	HDC MemDCBackground = CreateCompatibleDC(hdc);

	//캐릭터 담당
	HBITMAP OlbBitMapCharacter;
	HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
	BITMAP BitMapCharacterSize;	//이미지 파일 크기를 구하기 위한 비트맵
	HDC MemDCCharacter = CreateCompatibleDC(hdc);

	


	//캐릭터 그리는 파트
	GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapCharacterSize);
	int CharacterSizeX = BitMapCharacterSize.bmWidth;
	int CharacterSizeY = BitMapCharacterSize.bmHeight;

	TransparentBlt(MemDCFront, CHARACTER_LOCATION_X, YLocation, CharacterSizeX, CharacterSizeY, MemDCCharacter, 0, 0, CharacterSizeX, CharacterSizeY, RGB(255, 0, 255));
	//캐릭터 그리는 파트 끝


	BitBlt(hdc, 0, 0, 1024, 768, MemDCFront, 0, 0, SRCCOPY);	//본 화면에 출력



	SelectObject(MemDCFront, OldBitMapFront);



	DeleteObject(BitMapFront);
	DeleteDC(MemDCFront);
	DeleteDC(MemDCBackground);
	DeleteDC(MemDCCharacter);
}