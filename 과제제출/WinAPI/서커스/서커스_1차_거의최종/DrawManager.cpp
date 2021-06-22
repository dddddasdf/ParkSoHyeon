#include "DrawManager.h"

#define TEST_LOCATION 500	//테스트할 때 임시 좌표

void DrawManager::Init(HWND hWnd, HDC hdc)
{
	//윈도우 크기 구해서 사이즈 멤버 변수에 넣어두기
	RECT WindowRect;
	GetWindowRect(hWnd, &WindowRect);
	m_WindowWidth = WindowRect.right - WindowRect.left;
	m_WindowHeight = WindowRect.bottom - WindowRect.top;

	m_MemDCBack = CreateCompatibleDC(hdc);	//멤버 변수로 있던 DC 생성


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//오브젝트 클래스 초기화

	FireRing1 = new Ring1(hdc, DEFAULT_RING1_START);
	FireRing2 = new Ring1(hdc, DEFAULT_RING2_START);
	LittleFireRing = new LittleRing(hdc, DEFAULT_LITTLERING_START);
	Cash1 = new Cash(hdc, DEFAULT_LITTLERING_START);
	Map = new MapTile(hdc, NULL);






	////////////////////아래놈들 다 지울 예정

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

		HBitmapTmp = ResourceMgr->ReturnObstacleImage(OBSTACLE_CASH);
		GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);

		m_CashSizeWidth = BitmapTmp.bmWidth;
		m_CashSizeHeight = BitmapTmp.bmHeight;	//돈주머니 사이즈

		HBitmapTmp = ResourceMgr->ReturnObstacleImage(OBSTACLE_FIRE_1);
		GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);

		m_FireSizeWidth = BitmapTmp.bmWidth;
		m_FireSizeHeight = BitmapTmp.bmHeight;	//화로 사이즈
	}
	
	//Y좌표 시작 부분
	m_FloorYStart = HORIZON_HEIGHT - m_FloorImageSizeHeight;	//바닥 타일 시작 Y좌표
	m_CrowdYStart = HORIZON_HEIGHT - m_FloorImageSizeHeight - m_CrowdImageSizeHeight;	//관중 타일 시작 Y좌표

	{
		////화로 X좌표 벡터 저장
		//if (!m_ObstacleFireXLocation.empty())
		//	m_ObstacleFireXLocation.clear();	//이거 지금 안 쓰는 중임
		//
		//for (int i = FIRE_DISTANCE; i <= END_OF_MAP; i += FIRE_DISTANCE)
		//	m_ObstacleFireXLocation.push_back(i);	//화로는 500픽셀 간격으로 배치되어 있다

		m_FireAnimation = OBSTACLE_FIRE_1;	//겸사겸사 화로 애니메이션을 위한 멤버변수도 초기화
	}
}

void DrawManager::DeadInit()
{
	//X좌표만 처음 위치로 되돌려 주면 된다

	FireRing1->SetLocationX(DEFAULT_RING1_START);
	FireRing1->SetLocationX(DEFAULT_RING2_START);
	LittleFireRing->SetLocationX(DEFAULT_LITTLERING_START);
	Cash1->SetLocationX(DEFAULT_LITTLERING_START);
}

void DrawManager::DrawImages(HDC hdc, const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation)
{	
	//본 화면
	
	HBITMAP BitMapBack = CreateDIBSectionRe(hdc, m_WindowWidth, m_WindowHeight);
	HBITMAP OldBitMapBack = (HBITMAP)SelectObject(m_MemDCBack, BitMapBack);

	BITMAP BitMapImageSize;	//이미지 파일 크기를 구하기 위한 비트맵

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//배경 담당
	Map->Draw(m_MemDCBack, CharacterXLocation);

	//배경 그리는 파트 끝

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//장애물 담당
	HDC MemDCObstacle = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapObstacle;
	HBITMAP BitMapObstacle = NULL;

	//장애물 그리는 파트1 (불 고리 왼쪽 면, 화로)

	//불 고리 왼쪽 그림
	{
		FireRing1->Draw(m_MemDCBack, CharacterXLocation);
		FireRing2->Draw(m_MemDCBack, CharacterXLocation);		
	}

	//작은 불 고리 왼쪽 그림
	{
		LittleFireRing->Draw(m_MemDCBack, CharacterXLocation);
	}

	//돈주머니 그림 - m_IsCashSwitchOn이 true일 때만 그리는 함수를 실행한다
	{
		Cash1->Draw(m_MemDCBack, CharacterXLocation);
	}

	//화로 그림
	{
		switch (m_FireAnimation)
		{
		case OBSTACLE_FIRE_1:
			BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_FIRE_1);
			m_FireAnimation = OBSTACLE_FIRE_2;	//비트맵을 받아온 다음 애니메이션 관리 변수를 미리 다음 걸로 교체해서 다음 프레임 출력 때 바로바로 변경된 변수가 되도록 한다
			break;
		case OBSTACLE_FIRE_2:
			BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_FIRE_2);
			m_FireAnimation = OBSTACLE_FIRE_1;
			break;
		}

		OlbBitMapObstacle = (HBITMAP)SelectObject(MemDCObstacle, BitMapObstacle);

		for (int i = FIRE_DISTANCE - (CharacterXLocation % FIRE_DISTANCE) - 40; i <= m_WindowWidth; i += FIRE_DISTANCE)
		{
			//일정 간격으로 화로 출력
			/*
			유저의 맵에서의 X좌표를 기준으로 출력하게끔 한다. 화로는 영점에서부터 600 간격으로 놓여져 있다... 유저의 위치를 화로 간격으로 나눈 나머지값을 통해 다음 화로까지의 거리를 구하여
			출력한다

			-40이 있는 이유: 유저 뒷쪽에 있는 화로도 온전히 출력하기 위해서
			*/

			TransparentBlt(m_MemDCBack, i, HORIZON_FIRE - m_FireSizeWidth, m_FireSizeWidth, m_FireSizeHeight, MemDCObstacle, 0, 0, m_FireSizeWidth, m_FireSizeHeight, RGB(255, 0, 255));
		}
	}

	//장애물 그리는 파트1 끝

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//캐릭터 그리는 파트
	
	//캐릭터 담당
	HDC MemDCCharacter = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapCharacter;
	HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);

	{
		//그리는 연산
		GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapImageSize);
		int CharacterSizeX = BitMapImageSize.bmWidth;
		int CharacterSizeY = BitMapImageSize.bmHeight;

		OlbBitMapCharacter = (HBITMAP)SelectObject(MemDCCharacter, BitMapCharacter);
		TransparentBlt(m_MemDCBack, CHARACTER_LOCATION_X, CharacterYLocation - CharacterSizeY, CharacterSizeX, CharacterSizeY, MemDCCharacter, 0, 0, CharacterSizeX, CharacterSizeY, RGB(255, 0, 255));
		SelectObject(MemDCCharacter, OlbBitMapCharacter);		
	}
	
	//캐릭터 그리는 파트 끝
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//장애물 그리는 파트2 (불 고리 오른쪽 면)
	
	//불 고리 오른쪽 그림
	{
		FireRing1->Draw(m_MemDCBack, CharacterXLocation);
		FireRing2->Draw(m_MemDCBack, CharacterXLocation);
	}

	//작은 불 고리 오른쪽 그림
	{
		LittleFireRing->Draw(m_MemDCBack, CharacterXLocation);
	}


	SelectObject(MemDCObstacle, OlbBitMapObstacle);

	//장애물 그리는 파트2 끝

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	BitBlt(hdc, 0, 0, m_WindowWidth, m_WindowHeight, m_MemDCBack, 0, 0, SRCCOPY);	//본 화면에 출력
	SelectObject(m_MemDCBack, OldBitMapBack);


	DeleteDC(MemDCCharacter);
	DeleteDC(MemDCObstacle);
	DeleteObject(BitMapBack);
	/////////////////////////////////////////////////////////////////////////////////////////////////

}

void DrawManager::MoveRings(float MovingRingPixel, float MovingLittleRingPixel, int CharacterLocationX)
{
	FireRing1->RingMoving(MovingRingPixel, CharacterLocationX);
	FireRing2->RingMoving(MovingRingPixel, CharacterLocationX);
	LittleFireRing->RingMoving(MovingLittleRingPixel, CharacterLocationX);
	Cash1->CashMoving(MovingLittleRingPixel, CharacterLocationX);
}

bool DrawManager::IsCashCollision(const int& MotionNumber, const int& CharacterYLocation)
{
	if (true == m_IsCashSwitchOn)
	{
		//돈주머니가 젠 되어있을 때만 체크하면 된다... 먹어서 없는 동안에는 연산 돌려봐야 무의미
		HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
		BITMAP BitMapImageSize;

		GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapImageSize);
		int CharacterSizeX = BitMapImageSize.bmWidth;
		int CharacterSizeY = BitMapImageSize.bmHeight;
		//여기까지 캐릭터 비트맵 사이즈 구하는 부분

		RECT TmpRect;
		RECT PlayerRect = { CHARACTER_LOCATION_X, CharacterYLocation - CharacterSizeY, CHARACTER_LOCATION_X + CharacterSizeX, CharacterYLocation };
		RECT CashRect = { m_LittleRingXLocation - (m_CashSizeWidth * 0.5f), RING_LOCATION_Y + 25, m_LittleRingXLocation + (m_CashSizeWidth * 0.5f), (RING_LOCATION_Y + 25) + m_CashSizeHeight };

		if (IntersectRect(&TmpRect, &PlayerRect, &CashRect))
		{
			m_IsCashSwitchOn = false;
			return true;	//부딪친 것에 대해 참을 반환한다
		}
	}

	return false;	//아무 일도 없었으면 false 반환
}

bool DrawManager::IsObstacleCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation)
{
	HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
	BITMAP BitMapImageSize;

	GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapImageSize);
	int CharacterSizeX = BitMapImageSize.bmWidth;
	int CharacterSizeY = BitMapImageSize.bmHeight;
	//여기까지 캐릭터 비트맵 사이즈 구하는 부분

	RECT TmpRect;
	RECT PlayerRect = { CharacterXLocation, CharacterYLocation - CharacterSizeY, CharacterXLocation + CharacterSizeX, CharacterYLocation };	//유저 사각형(안 보임)

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//화로와 부딪쳤는지 체크함
	{
		int FireXLocation = FIRE_DISTANCE - (CharacterXLocation % FIRE_DISTANCE) - 40 + CharacterXLocation - m_FireSizeWidth + 25;

		RECT FireRectLeft = { FireXLocation, HORIZON_FIRE - m_FireSizeHeight + 10, FireXLocation + m_FireSizeWidth - 15, HORIZON_FIRE };
		RECT FireRectRight = { FireXLocation + FIRE_DISTANCE, HORIZON_FIRE - m_FireSizeHeight + 10, (FireXLocation + FIRE_DISTANCE) + m_FireSizeWidth - 15, HORIZON_FIRE };
		//버그가 아닌 이상 유저 앞의 두번째 화로와 부딪칠 일은 없으므로 유저 뒷쪽의 화로 하나 오른쪽의 화로 하나만 체크하면 될지도 모름
		//판정 너무 빡세서 상수 조금씩 보태가며 보정해주는 중임...

		if (IntersectRect(&TmpRect, &PlayerRect, &FireRectLeft))
		{
			return true;	//부딪친 것에 대해 참을 반환한다
		}
		if (IntersectRect(&TmpRect, &PlayerRect, &FireRectRight))
		{
			return true;	//부딪친 것에 대해 참을 반환한다
		}
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//고리와 부딪쳤는지 체크함
	//고리는 윗부분 아랫부분으로 쪼개서 그 둘과 부딪쳤는지 체크한다

	//{
	//	BITMAP BitMapSize;
	//	HBITMAP BitMapObstacle = NULL;
	//	switch (m_RingAnimation)
	//	{
	//	case OBSTACLE_RING_FIRST_1:
	//		BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_RING_FIRST_1);
	//		break;
	//	case OBSTACLE_RING_SECOND_1:
	//		BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_RING_SECOND_1);
	//		break;
	//	}

	//	GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);	//고리 비트맵 사이즈 구함
	//	int RingSizeY = BitMapImageSize.bmHeight;

	//	RECT Ring1RectUp = { m_Ring1XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y, m_Ring1XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y - RING_COLLISION_HEIGHT_PIEXL };
	//	RECT Ring1RectDown = { m_Ring1XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY - RING_COLLISION_HEIGHT_PIEXL,
	//		m_Ring1XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY };
	//	RECT Ring2RectUp = { m_Ring2XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y, m_Ring2XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y - RING_COLLISION_HEIGHT_PIEXL };
	//	RECT Ring2RectDown = { m_Ring2XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY - RING_COLLISION_HEIGHT_PIEXL,
	//		m_Ring2XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY };

	//	BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_LITTLERING_1);

	//	GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);	//고리 비트맵 사이즈 구함
	//	RingSizeY = BitMapImageSize.bmHeight;

	//	RECT LittleRingRectUp = { m_LittleRingXLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y, m_LittleRingXLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y - RING_COLLISION_HEIGHT_PIEXL };
	//	RECT LittleRingRectDown = { m_LittleRingXLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY - RING_COLLISION_HEIGHT_PIEXL,
	//		m_LittleRingXLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY };

	//	if (IntersectRect(&TmpRect, &PlayerRect, &Ring1RectUp) || IntersectRect(&TmpRect, &PlayerRect, &Ring1RectDown) || IntersectRect(&TmpRect, &PlayerRect, &Ring2RectUp)
	//	|| IntersectRect(&TmpRect, &PlayerRect, &Ring2RectDown) || IntersectRect(&TmpRect, &PlayerRect, &LittleRingRectUp) || IntersectRect(&TmpRect, &PlayerRect, &LittleRingRectDown))
	//	{
	//		return true;	//부딪친 것에 대해 참을 반환한다
	//	}
	//}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return false; //아무것도 안 부딪침
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


DrawManager::~DrawManager()
{
	DeleteDC(m_MemDCBack);
}