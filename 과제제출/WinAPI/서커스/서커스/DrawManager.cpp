#include "DrawManager.h"

#define TEST_LOCATION 500	//테스트할 때 임시 좌표

void DrawManager::DrawImages(HDC hdc, int MotionNumber, int YLocation)
{
	//본 화면
	HBITMAP OldBitMapFront;
	HBITMAP BitMapFront = NULL;
	HDC MemDCFront = CreateCompatibleDC(hdc);
	

	//배경 담당
	/*HBITMAP OlbBitMapBackground;
	HBITMAP BitMapBackground = NULL;
	HDC MemDCBackground = CreateCompatibleDC(hdc);*/

	//캐릭터 담당
	HBITMAP OlbBitMapCharacter;
	HBITMAP BitMapCharacter = NULL;
	HDC MemDCCharacter = CreateCompatibleDC(hdc);
	BITMAP BitMapCharacterSize;	//이미지 파일 크기를 구하기 위한 비트맵



	//캐릭터 그리는 파트
	BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
	OlbBitMapCharacter = (HBITMAP)SelectObject(MemDCCharacter, BitMapCharacter);
	
	GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapCharacterSize);
	int CharacterSizeX = BitMapCharacterSize.bmWidth;
	int CharacterSizeY = BitMapCharacterSize.bmHeight;

	

	TransparentBlt(MemDCFront, CHARACTER_LOCATION_X, YLocation, CharacterSizeX, CharacterSizeY, MemDCCharacter, 0, 0, CharacterSizeX, CharacterSizeY, RGB(255, 0, 255));
	//캐릭터 그리는 파트 끝

	OldBitMapFront = (HBITMAP)SelectObject(MemDCFront, BitMapFront);

	BitBlt(hdc, 0, 0, 1024, 768, MemDCFront, 0, 0, SRCCOPY);	//본 화면에 출력

	SelectObject(MemDCFront, OldBitMapFront);

	//DeleteObject(BitMapFront);
	DeleteDC(MemDCFront);
	//DeleteDC(MemDCBackground);
	DeleteDC(MemDCCharacter);


	//HBITMAP OldBitMap;
	//HBITMAP BitMap = NULL;
	//HDC MemDC = CreateCompatibleDC(hdc);
	//BITMAP BitMapCharacterSize;	//이미지 파일 크기를 구하기 위한 비트맵
	//

	////필요한 그림 불러오는 부분
	//BitMap = ResourceMgr->ReturnCharacterImage(MotionNumber);
	//GetObject(BitMap, sizeof(BITMAP), &BitMapCharacterSize);

	//if (BitMap == NULL)
	//{
	//	//IsEmpty가 NULL이 아닐 때만 출력 작업 시도... NULL이면 return으로 돌아간다

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