#include "DrawManager.h"

#define TEST_LOCATION 500	//�׽�Ʈ�� �� �ӽ� ��ǥ

void DrawManager::Init(HWND hWnd)
{
	//������ ũ�� ���ؼ� ������ ��� ������ �־�α�
	RECT WindowRect;
	GetWindowRect(hWnd, &WindowRect);
	m_WindowWidth = WindowRect.right - WindowRect.left;
	m_WindowHeight = WindowRect.bottom - WindowRect.top;

	//��� �� Ÿ�� ���� ����
	if (!m_BackgroundTileVector.empty())
		m_BackgroundTileVector.clear();

	m_BackgroundTileVector.push_back(BACKGROUND_ELEPHANT);
	for (int i = 1; i <= 6; i++)
	{
		if (1 == i % 2)
			m_BackgroundTileVector.push_back(BACKGROUND_CROWD_FIRST);
		else
			m_BackgroundTileVector.push_back(BACKGROUND_CROWD_SECOND);
	}
}

void DrawManager::DrawImages(HDC hdc, const int& MotionNumber, const int& YLocation)
{	
	//�� ȭ��
	HDC MemDCBack = CreateCompatibleDC(hdc);
	HBITMAP BitMapBack = CreateDIBSectionRe(hdc, m_WindowWidth, m_WindowHeight);
	HBITMAP OldBitMapBack = (HBITMAP)SelectObject(MemDCBack, BitMapBack);

	BITMAP BitMapImageSize;	//�̹��� ���� ũ�⸦ ���ϱ� ���� ��Ʈ��

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��� ���
	HDC MemDCBackground = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapBackground;
	HBITMAP BitMapBackground = NULL;


	//��� �׸��� ��Ʈ
	BitMapBackground = ResourceMgr->ReturnBackgroundImage(BACKGROUND_FLOOR);
	GetObject(BitMapBackground, sizeof(BITMAP), &BitMapImageSize);
	int ImageSizeX = BitMapImageSize.bmWidth;
	int ImageSizeY = BitMapImageSize.bmHeight;

	OlbBitMapBackground = (HBITMAP)SelectObject(MemDCBackground, BitMapBackground);

	for (int i = 0; i < (m_WindowWidth / ImageSizeX + 1); i++)
	{
		TransparentBlt(MemDCBack, 0 + ImageSizeX * i, HORIZON_HEIGHT - ImageSizeY, ImageSizeX, ImageSizeY, MemDCBackground, 0, 0, ImageSizeX, ImageSizeY, RGB(255, 0, 255));
		SelectObject(MemDCBackground, OlbBitMapBackground);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ĳ���� ���
	HDC MemDCCharacter = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapCharacter;
	HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
	


	//ĳ���� �׸��� ��Ʈ
	GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapImageSize);
	int CharacterSizeX = BitMapImageSize.bmWidth;
	int CharacterSizeY = BitMapImageSize.bmHeight;

	OlbBitMapCharacter = (HBITMAP)SelectObject(MemDCCharacter, BitMapCharacter);
	TransparentBlt(MemDCBack, CHARACTER_LOCATION_X, YLocation, ImageSizeX, ImageSizeY, MemDCCharacter, 0, 0, ImageSizeX, ImageSizeY, RGB(255, 0, 255));
	SelectObject(MemDCCharacter, OlbBitMapCharacter);
	//ĳ���� �׸��� ��Ʈ ��

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	BitBlt(hdc, 0, 0, m_WindowWidth, m_WindowHeight, MemDCBack, 0, 0, SRCCOPY);	//�� ȭ�鿡 ���
	SelectObject(MemDCBack, OldBitMapBack);


	DeleteDC(MemDCCharacter);
	DeleteDC(MemDCBackground);
	DeleteDC(MemDCBack);
	DeleteObject(BitMapBack);
	/////////////////////////////////////////////////////////////////////////////////////////////////

	//HBITMAP OldBitMap;
	//HBITMAP BitMap = NULL;
	//HDC MemDC = CreateCompatibleDC(hdc);
	//BITMAP BitMapCharacterSize;	//�̹��� ���� ũ�⸦ ���ϱ� ���� ��Ʈ��
	//

	////�ʿ��� �׸� �ҷ����� �κ�
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
	bm_info.bmiHeader.biBitCount = 24;  // �÷� ��(color bits) : 1, 4, 8, 16, 24, 31
	bm_info.bmiHeader.biWidth = width;  // �ʺ�.
	bm_info.bmiHeader.biHeight = height;// ����.
	bm_info.bmiHeader.biPlanes = 1;

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}