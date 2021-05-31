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
	for (int i = 1; i <= CROWD_PATTERN; i++)
	{
		m_BackgroundTileVector.push_back(BACKGROUND_CROWD_FIRST);
	}

	//�� �̹��� ������ �̸� ���س���
	HBITMAP HBitmapTmp;
	BITMAP BitmapTmp;

	HBitmapTmp = ResourceMgr->ReturnBackgroundImage(BACKGROUND_FLOOR);
	GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);

	m_FloorImageSizeWidth = BitmapTmp.bmWidth;
	m_FloorImageSizeHeight = BitmapTmp.bmHeight;	//�ٴ� ������

	HBitmapTmp = ResourceMgr->ReturnBackgroundImage(BACKGROUND_CROWD_FIRST);
	GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);

	m_CrowdImageSizeWidth = BitmapTmp.bmWidth;
	m_CrowdImageSizeHeight = BitmapTmp.bmHeight;	//���� ������

	//Y��ǥ ���� �κ�
	m_FloorYStart = HORIZON_HEIGHT - m_FloorImageSizeHeight;
	m_CrowdYStart = HORIZON_HEIGHT - m_FloorImageSizeHeight - m_CrowdImageSizeHeight;
}

void DrawManager::DrawImages(HDC hdc, const int& MotionNumber, const int& XLocation, const int& YLocation)
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


	//��� �׸��� ��Ʈ - �ٴ�
	BitMapBackground = ResourceMgr->ReturnBackgroundImage(BACKGROUND_FLOOR);
	OlbBitMapBackground = (HBITMAP)SelectObject(MemDCBackground, BitMapBackground);

	for (int i = 0; i < (m_WindowWidth / m_FloorImageSizeWidth + 1); i++)
	{
		TransparentBlt(MemDCBack, m_FloorImageSizeWidth * i, m_FloorYStart, m_FloorImageSizeWidth, m_FloorImageSizeHeight, 
			MemDCBackground, 0, 0, m_FloorImageSizeWidth, m_FloorImageSizeHeight, RGB(255, 0, 255));
	}


	//��� �׸��� ��Ʈ - ����
	int StartBlock = XLocation / m_CrowdImageSizeWidth;	//�÷��̾� ��ġ�� ���� ������ ���� ���ؾ� ��
	int CutWidth = XLocation - (m_CrowdImageSizeWidth * StartBlock);	//�÷��̾��� �� X ��ǥ�� ���� �߸��� ĭ�� ���� ���
	for (int i = StartBlock, j = 0; i < (m_WindowWidth / m_CrowdImageSizeWidth + (StartBlock +1)); i++, j++)
	{
		BitMapBackground = ResourceMgr->ReturnBackgroundImage((m_BackgroundTileVector.at(i % CROWD_PATTERN)));
		OlbBitMapBackground = (HBITMAP)SelectObject(MemDCBackground, BitMapBackground);
		TransparentBlt(MemDCBack, (0 - CutWidth) + m_CrowdImageSizeWidth * j, m_CrowdYStart, m_CrowdImageSizeWidth, m_CrowdImageSizeHeight,
			MemDCBackground, 0, 0, m_CrowdImageSizeWidth, m_CrowdImageSizeHeight, RGB(255, 0, 255));
	}
	/*
	CutWidth�� �켱 ù��° Ÿ���� �߸��� ���̸� ���Ѵ�
	�׸��� ������ǥ�� x = 0���� �߸��� ���̸�ŭ ������ �ּ� �����ϰ� �Ѵ�
	������ Ÿ�ϵ��� Ÿ���� ������ ����(j)�� Ÿ���� ���̸� ���ؼ� �׷����� x��ǥ�� ���Ѵ�
	*/

	SelectObject(MemDCBackground, OlbBitMapBackground);

	//��� �׸��� ��Ʈ ��

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ĳ���� ���
	HDC MemDCCharacter = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapCharacter;
	HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
	

	//ĳ���� �׸��� ��Ʈ
	GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapImageSize);
	int CharacterSizeX = BitMapImageSize.bmWidth;
	int CharacterSizeY = BitMapImageSize.bmHeight;

	OlbBitMapCharacter = (HBITMAP)SelectObject(MemDCCharacter, BitMapCharacter);
	TransparentBlt(MemDCBack, CHARACTER_LOCATION_X, YLocation - CharacterSizeY, CharacterSizeX, CharacterSizeY, MemDCCharacter, 0, 0, CharacterSizeX, CharacterSizeY, RGB(255, 0, 255));
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