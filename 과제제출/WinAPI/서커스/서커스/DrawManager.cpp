#include "DrawManager.h"

#define TEST_LOCATION 500	//테스트할 때 임시 좌표

void DrawManager::Init(HWND hWnd)
{
	//윈도우 크기 구해서 사이즈 멤버 변수에 넣어두기
	RECT WindowRect;
	GetWindowRect(hWnd, &WindowRect);
	m_WindowWidth = WindowRect.right - WindowRect.left;
	m_WindowHeight = WindowRect.bottom - WindowRect.top;

	{
		//배경 맵 타일-군중 벡터 저장
		if (!m_BackgroundTileVector.empty())
			m_BackgroundTileVector.clear();

		m_BackgroundTileVector.push_back(BACKGROUND_ELEPHANT);
		for (int i = 1; i <= CROWD_PATTERN; i++)
		{
			m_BackgroundTileVector.push_back(BACKGROUND_CROWD_FIRST);
		}
	}
	
	{
		//각 이미지 사이즈 미리 구해놓기
		HBITMAP HBitmapTmp;
		BITMAP BitmapTmp;

		HBitmapTmp = ResourceMgr->ReturnBackgroundImage(BACKGROUND_FLOOR);
		GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);

		m_FloorImageSizeWidth = BitmapTmp.bmWidth;
		m_FloorImageSizeHeight = BitmapTmp.bmHeight;	//바닥 사이즈

		HBitmapTmp = ResourceMgr->ReturnBackgroundImage(BACKGROUND_CROWD_FIRST);
		GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);

		m_CrowdImageSizeWidth = BitmapTmp.bmWidth;
		m_CrowdImageSizeHeight = BitmapTmp.bmHeight;	//군중 사이즈

	}
	
	//Y좌표 시작 부분
	m_FloorYStart = HORIZON_HEIGHT - m_FloorImageSizeHeight;	//바닥 타일 시작 Y좌표
	m_CrowdYStart = HORIZON_HEIGHT - m_FloorImageSizeHeight - m_CrowdImageSizeHeight;	//관중 타일 시작 Y좌표

	{
		//화로 X좌표 벡터 저장
		if (!m_ObstacleFireXLocation.empty())
			m_ObstacleFireXLocation.clear();

		for (int i = 300; i <= END_OF_MAP; i += 500)
			m_ObstacleFireXLocation.push_back(i);	//화로는 500픽셀 간격으로 배치되어 있다

		m_FireAnimation = OBSTACLE_FIRE_1;	//겸사겸사 화로 애니메이션을 위한 멤버변수도 초기화
	}
}

void DrawManager::DrawImages(HDC hdc, const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation)
{	
	//본 화면
	HDC MemDCBack = CreateCompatibleDC(hdc);
	HBITMAP BitMapBack = CreateDIBSectionRe(hdc, m_WindowWidth, m_WindowHeight);
	HBITMAP OldBitMapBack = (HBITMAP)SelectObject(MemDCBack, BitMapBack);

	BITMAP BitMapImageSize;	//이미지 파일 크기를 구하기 위한 비트맵

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//배경 담당
	HDC MemDCBackground = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapBackground;
	HBITMAP BitMapBackground = NULL;


	//배경 그리는 파트 - 바닥
	BitMapBackground = ResourceMgr->ReturnBackgroundImage(BACKGROUND_FLOOR);
	OlbBitMapBackground = (HBITMAP)SelectObject(MemDCBackground, BitMapBackground);

	for (int i = 0; i < (m_WindowWidth / m_FloorImageSizeWidth + 1); i++)
	{
		TransparentBlt(MemDCBack, m_FloorImageSizeWidth * i, m_FloorYStart, m_FloorImageSizeWidth, m_FloorImageSizeHeight, 
			MemDCBackground, 0, 0, m_FloorImageSizeWidth, m_FloorImageSizeHeight, RGB(255, 0, 255));
	}


	//배경 그리는 파트 - 군중
	int StartBlock = CharacterXLocation / m_CrowdImageSizeWidth;	//플레이어 위치에 따라 시작할 블럭을 정해야 함
	int CutWidth = CharacterXLocation - (m_CrowdImageSizeWidth * StartBlock);	//플레이어의 맵 X 좌표에 따라 잘리는 칸의 길이 계산
	for (int i = StartBlock, j = 0; i < (m_WindowWidth / m_CrowdImageSizeWidth + (StartBlock +1)); i++, j++)
	{
		BitMapBackground = ResourceMgr->ReturnBackgroundImage((m_BackgroundTileVector.at(i % CROWD_PATTERN)));
		OlbBitMapBackground = (HBITMAP)SelectObject(MemDCBackground, BitMapBackground);
		TransparentBlt(MemDCBack, (0 - CutWidth) + m_CrowdImageSizeWidth * j, m_CrowdYStart, m_CrowdImageSizeWidth, m_CrowdImageSizeHeight,
			MemDCBackground, 0, 0, m_CrowdImageSizeWidth, m_CrowdImageSizeHeight, RGB(255, 0, 255));
	}
	/*
	CutWidth로 우선 첫번째 타일의 잘리는 길이를 구한다
	그리기 시작좌표를 x = 0에서 잘리는 길이만큼 앞으로 둬서 시작하게 한다
	이후의 타일들은 타일이 놓여진 개수(j)에 타일의 길이를 곱해서 그려지는 x좌표를 구한다
	*/

	SelectObject(MemDCBackground, OlbBitMapBackground);

	//배경 그리는 파트 끝

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//장애물 담당
	HDC MemDCObstacle = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapObstacle;
	HBITMAP BitMapObstacle = NULL;

	//장애물 그리는 파트1 (불 고리 왼쪽 면)


	//장애물 그리는 파트1 끝

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//캐릭터 담당
	HDC MemDCCharacter = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapCharacter;
	HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
	

	//캐릭터 그리는 파트
	GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapImageSize);
	int CharacterSizeX = BitMapImageSize.bmWidth;
	int CharacterSizeY = BitMapImageSize.bmHeight;

	OlbBitMapCharacter = (HBITMAP)SelectObject(MemDCCharacter, BitMapCharacter);
	TransparentBlt(MemDCBack, CHARACTER_LOCATION_X, CharacterYLocation - CharacterSizeY, CharacterSizeX, CharacterSizeY, MemDCCharacter, 0, 0, CharacterSizeX, CharacterSizeY, RGB(255, 0, 255));
	SelectObject(MemDCCharacter, OlbBitMapCharacter);
	//캐릭터 그리는 파트 끝

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//장애물 그리는 파트2 (불 고리 오른쪽 면, 화로)

	//화로 그림
	switch (m_FireAnimation)
	{
	case OBSTACLE_FIRE_1:
		BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_FIRE_1);
		m_FireAnimation = OBSTACLE_FIRE_2;	//비트맵을 받아온 다음 애니메이션 변수를 미리 다음 걸로 교체해서 다음 프레임 출력 때 바로바로 변경된 변수이도록 한다
		break;
	case OBSTACLE_FIRE_2:
		BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_FIRE_2);
		m_FireAnimation = OBSTACLE_FIRE_1;
		break;
	}

	GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);
	int FireSizeX = BitMapImageSize.bmWidth;
	int FireSizeY = BitMapImageSize.bmHeight;

	for (int i = 500 - (CharacterXLocation % FIRE_DISTANCE) - 40; i <= m_WindowWidth; i += 500)
	{
		//일정 간격으로 화로 출력
		OlbBitMapObstacle = (HBITMAP)SelectObject(MemDCObstacle, BitMapObstacle);
		TransparentBlt(MemDCBack, i, HORIZON_FIRE - FireSizeY, FireSizeX, FireSizeY, MemDCObstacle, 0, 0, FireSizeX, FireSizeY, RGB(255, 0, 255));
		SelectObject(MemDCObstacle, OlbBitMapObstacle);
	}

	



	//장애물 그리는 파트2 끝

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	BitBlt(hdc, 0, 0, m_WindowWidth, m_WindowHeight, MemDCBack, 0, 0, SRCCOPY);	//본 화면에 출력
	SelectObject(MemDCBack, OldBitMapBack);


	DeleteDC(MemDCCharacter);
	DeleteDC(MemDCBackground);
	DeleteDC(MemDCBack);
	DeleteDC(MemDCObstacle);
	DeleteObject(BitMapBack);
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