#include "DrawManager.h"

#define TEST_LOCATION 500	//테스트할 때 임시 좌표

void DrawManager::DrawImages(HDC hdc, HWND hWnd, const int& MotionNumber, const int& YLocation)
{
	//윈도우 크기 구하기
	RECT WindowRect;
	GetWindowRect(hWnd, &WindowRect);
	
	//본 화면
	HDC MemDCBack = CreateCompatibleDC(hdc);
	HBITMAP BitMapBack = CreateDIBSectionRe(hdc, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top);
	HBITMAP OldBitMapBack = (HBITMAP)SelectObject(MemDCBack, BitMapBack);
	
	//배경 담당
	/*HBITMAP OlbBitMapBackground;
	HBITMAP BitMapBackground = NULL;
	HDC MemDCBackground = CreateCompatibleDC(hdc);*/

	//캐릭터 담당
	HDC MemDCCharacter = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapCharacter ;
	HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
	BITMAP BitMapCharacterSize;	//이미지 파일 크기를 구하기 위한 비트맵


	//캐릭터 그리는 파트
	GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapCharacterSize);
	int CharacterSizeX = BitMapCharacterSize.bmWidth;
	int CharacterSizeY = BitMapCharacterSize.bmHeight;

	OlbBitMapCharacter = (HBITMAP)SelectObject(MemDCCharacter, BitMapCharacter);
	TransparentBlt(MemDCBack, CHARACTER_LOCATION_X, YLocation, CharacterSizeX, CharacterSizeY, MemDCCharacter, 0, 0, CharacterSizeX, CharacterSizeY, RGB(255, 0, 255));
	SelectObject(MemDCCharacter, OlbBitMapCharacter);
	//캐릭터 그리는 파트 끝



	BitBlt(hdc, 0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, MemDCBack, 0, 0, SRCCOPY);	//본 화면에 출력
	SelectObject(MemDCBack, OldBitMapBack);


	DeleteDC(MemDCCharacter);
	DeleteDC(MemDCBack);
	DeleteObject(BitMapBack);
	//DeleteDC(MemDCBackground);
	/////////////////////////////////////////////////////////////////////////////////////////////////

	//HBITMAP OldBitMap;
	//HBITMAP BitMap = NULL;
	//HDC MemDC = CreateCompatibleDC(hdc);
	//BITMAP BitMapCharacterSize;	//이미지 파일 크기를 구하기 위한 비트맵
	//

	////필요한 그림 불러오는 부분
	//BitMap = ResourceMgr->ReturnCharacterImage(MotionNumber);
	//GetObject(BitMap, sizeof(BITMAP), &BitMapCharacterSize);


	//OldBitMap = (HBITMAP)SelectObject(MemDC, BitMap);

	//int CharacterSizeX = BitMapCharacterSize.bmWidth;
	//int CharacterSizeY = BitMapCharacterSize.bmHeight;

	//TransparentBlt(hdc, CHARACTER_LOCATION_X, YLocation, CharacterSizeX, CharacterSizeY, MemDC, 0, 0, CharacterSizeX, CharacterSizeY, RGB(255, 0, 255));

	//SelectObject(MemDC, OldBitMap);
	//DeleteDC(MemDC);
}

HBITMAP DrawManager::CreateDIBSectionRe(HDC hdc, int width, int height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));
	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bm_info.bmiHeader.biBitCount = 24;  // 컬러 수(color bits) : 1, 4, 8, 16, 24, 31
	bm_info.bmiHeader.biWidth = width;  // 너비.
	bm_info.bmiHeader.biHeight = height;// 높이.
	bm_info.bmiHeader.biPlanes = 1;

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}