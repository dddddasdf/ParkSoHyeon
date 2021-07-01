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

	FireRing1 = new Ring1(hdc, LOCATION_RING1_START);
	FireRing2 = new Ring1(hdc, LOCATION_RING2_START);
	LittleFireRing = new LittleRing(hdc, LOCATION_LITTLERING_START);
	Cash1 = new Cash(hdc, LOCATION_LITTLERING_START);
	Map = new MapTile(hdc, NULL);
	CharacterObject = new Character(hdc, NULL);


	//간단한 비트맵 받아두기... 오브젝트로 빼야 할 필요가 없다고 판단해서 목숨 표시는 비트맵으로만 굴림
	LifeImage = ResourceMgr->ReturnInterfaceBitMapClass(2);

	//폰트 설정... - 점수용
	m_FontCustomize = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "돋움");

	//화로 클래스 배열(벡터0 초기화
	
	for (int i = 1; i < (LOCATION_GOAL_X - FIRE_DISTANCE) / FIRE_DISTANCE; i++)
	{
		Fire *fire = new Fire(m_MemDCBack, FIRE_DISTANCE * i);
		m_FireVector.push_back(fire);
	}
}

void DrawManager::DeadInit()
{
	//X좌표만 처음 위치로 되돌려 주면 된다

	FireRing1->SetLocationX(LOCATION_RING1_START);
	FireRing2->SetLocationX(LOCATION_RING2_START);
	LittleFireRing->SetLocationX(LOCATION_LITTLERING_START);
	Cash1->SetLocationX(LOCATION_LITTLERING_START);
	Cash1->SwitchOnCash();	//점수 스위치 초기화

	//화로 점수 스위치 초기화
	for (int i = 0; i < ((LOCATION_GOAL_X - FIRE_DISTANCE) / FIRE_DISTANCE) - 1; i++)
	{
		(m_FireVector.at(i))->SwitchOnScore();
	}
}

void DrawManager::DrawImages(HDC hdc, const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation, const int& Life, const int& Score, const int& BonusScore)
{	
	if (m_WindowWidth >= LOCATION_GOAL_X - CharacterXLocation)
	{
		//골이 보이기 시작할 경우에 대하여...... 스크롤 제어를 위한 부분
	}
	
	
	//본 화면
	
	HBITMAP BitMapBack = CreateDIBSectionRe(hdc, m_WindowWidth, m_WindowHeight);
	HBITMAP OldBitMapBack = (HBITMAP)SelectObject(m_MemDCBack, BitMapBack);

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
		int Tmp = CharacterXLocation / FIRE_DISTANCE;	//몇번째 화로부터 출력해야 하는지 알기 위해 임시로 변수 구함

		(m_FireVector.at(Tmp))->Draw(m_MemDCBack, CharacterXLocation);
		(m_FireVector.at(Tmp + 1))->Draw(m_MemDCBack, CharacterXLocation);
		(m_FireVector.at(Tmp + 2))->Draw(m_MemDCBack, CharacterXLocation);
		//한 번에 3개만 출력하면 된다
	}

	//장애물 그리는 파트1 끝

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//캐릭터 그리는 파트

	CharacterObject->DrawChracater(m_MemDCBack, CharacterYLocation, MotionNumber);

	
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


	//장애물 그리는 파트2 끝

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//점수, 목숨 출력

	for (int i = Life; i > 0; i--)
	{
		(HBITMAP)SelectObject(MemDCObstacle, LifeImage.ReturnBitMap());
		TransparentBlt(m_MemDCBack, LOCATION_LIFE_X - LifeImage.ReturnBitMapWidth() * i, LOCATION_LIFE_Y, LifeImage.ReturnBitMapWidth(), LifeImage.ReturnBitMapHeight(), 
			MemDCObstacle, 0, 0, LifeImage.ReturnBitMapWidth(), LifeImage.ReturnBitMapHeight(), RGB(255, 0, 255));
	}

	//auto font = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "궁서");
	//SelectObject(m_MemDCBack, font);
	SelectObject(m_MemDCBack, m_FontCustomize);
	SetTextColor(m_MemDCBack, RGB(255, 255,255));
	SetBkMode(m_MemDCBack, TRANSPARENT);
	std::string str = std::to_string(Score);
	TextOut(m_MemDCBack, LOCATION_SCORE_X, LOCATION_SCORE_Y, str.c_str(), str.length());
	str = "Bonus: " + std::to_string(BonusScore);
	TextOut(m_MemDCBack, LOCATION_BONUS_SCORE_X, LOCATION_BONUS_SCORE_Y, str.c_str(), str.length());
	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef Debug_Coll
	Rectangle(m_MemDCBack, Ring1RectDown.left, Ring1RectDown.top, Ring1RectDown.right, Ring1RectDown.bottom);
	Rectangle(m_MemDCBack, Ring2RectDown.left, Ring2RectDown.top, Ring2RectDown.right, Ring2RectDown.bottom);
	Rectangle(m_MemDCBack, LittleRingRectDown.left, LittleRingRectDown.top, LittleRingRectDown.right, LittleRingRectDown.bottom);
	Rectangle(m_MemDCBack, CharacterRect.left, CharacterRect.top, CharacterRect.right, CharacterRect.bottom);
#endif // Debug_Coll

	BitBlt(hdc, 0, 0, m_WindowWidth, m_WindowHeight, m_MemDCBack, 0, 0, SRCCOPY);	//본 화면에 출력
	SelectObject(m_MemDCBack, OldBitMapBack);


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

bool DrawManager::IsCashCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation)
{
	//돈주머니와 부딪쳤는지 체크함
	//돈주머니가 젠 되어있을 때만 체크하면 된다... 먹어서 없는 동안에는 연산 돌려봐야 무의미
	if (Cash1->ReturnIsCashSwitched())
	{
		
		RECT TmpRect;
		RECT CharacterRectCash = { (CharacterXLocation + LOCATION_CHARACTER_VERTICAL) + (LONG)(CharacterObject->ReturnMemberBitMapWidth() * 0.5f) - HITBOX_CHARACTER_WIDTH, 
			CharacterYLocation - CharacterObject->ReturnMemberBitMapHeight(),
			(CharacterXLocation + LOCATION_CHARACTER_VERTICAL) + (LONG)(CharacterObject->ReturnMemberBitMapWidth() * 0.5f) + HITBOX_CHARACTER_WIDTH, CharacterYLocation - HITBOX_CHARACTER_HEIGHT_DOWN };
		//화면에 보이는 유저 위치 보정 때문에 CHARACTER_LOCATION_X을 추가해줘야 함
		//↑유저 사각형
		
		RECT CashRect = { Cash1->GetLocationX() - (Cash1->ReturnMemberBitMapWidth() * 0.5f), Cash1->GetLocationY(),
			Cash1->GetLocationX() + (Cash1->ReturnMemberBitMapWidth() * 0.5f), Cash1->GetLocationY() + Cash1->ReturnMemberBitMapHeight() };

		if (IntersectRect(&TmpRect, &CharacterRectCash, &CashRect))
		{
			Cash1->SwitchOffCash();	//부딪쳤으면 돈주머니 스위치 끄기
			return true;
		}
	}
	return false;	//아무 일도 없었으면 false 반환
}

int DrawManager::IsObsjectCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation)
{
	RECT TmpRect;
	CharacterRect = { CharacterXLocation + LOCATION_CHARACTER_VERTICAL, CharacterYLocation - CharacterObject->ReturnMemberBitMapHeight() + HITBOX_CHARACTER_HEIGHT_UP,
		CharacterXLocation + CharacterObject->ReturnMemberBitMapWidth() + (LONG)(LOCATION_CHARACTER_VERTICAL * 0.5f), CharacterYLocation - HITBOX_CHARACTER_HEIGHT_DOWN };	//화면에 보이는 유저 위치 보정 때문에 CHARACTER_LOCATION_X을 추가해줘야 함
	//↑유저 사각형

	int Score_Tmp = 0;	//넘은 장애물 수에 따라 보내줄 점수 임시
	int User_Tmp = CharacterXLocation + LOCATION_CHARACTER_VERTICAL + CharacterObject->ReturnMemberBitMapWidth() * 0.5f;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//화로와 부딪쳤는지 체크함
	int Fire_Tmp = CharacterXLocation / FIRE_DISTANCE;	//몇번째 화로부터 충돌 체크 해야 하는지 임시로 변수 구함
	{
		RECT FireRectLeft = { m_FireVector.at(Fire_Tmp)->GetLocationX() + (m_FireVector.at(Fire_Tmp)->ReturnMemberBitMapWidth() * 0.5f) - HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL,
			LOCATION_FIRE_Y - HITBOX_FIRE_UP,
			m_FireVector.at(Fire_Tmp)->GetLocationX() + (m_FireVector.at(Fire_Tmp)->ReturnMemberBitMapWidth() * 0.5f) + HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL,
			LOCATION_FIRE_Y };
		RECT FireRectRight = { m_FireVector.at(Fire_Tmp + 1)->GetLocationX() + (m_FireVector.at(Fire_Tmp + 1)->ReturnMemberBitMapWidth() * 0.5f) - HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL, 
			LOCATION_FIRE_Y - HITBOX_FIRE_UP,
			m_FireVector.at(Fire_Tmp + 1)->GetLocationX() + (m_FireVector.at(Fire_Tmp + 1)->ReturnMemberBitMapWidth() * 0.5f) + HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL, LOCATION_FIRE_Y };

		if (IntersectRect(&TmpRect, &CharacterRect, &FireRectLeft) || IntersectRect(&TmpRect, &CharacterRect, &FireRectRight))
		{
			return CRASHED_OBJECT;	//부딪친 것에 대해 참을 반환한다
		}

		//LOCATION_CHARACTER_VERTICAL는 위치에 대한 보정값
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//고리와 부딪쳤는지 체크함
	//고리는 윗부분 아랫부분으로 쪼개서 그 둘과 부딪쳤는지 체크한다
	{
		Ring1RectDown = { FireRing1->GetLocationX() - HITBOX_RING_WIDTH, LOCATION_RING_Y + FireRing1->ReturnMemberBitMapHeight() - HITBOX_RING_HEIGHT,
		FireRing1->GetLocationX() + HITBOX_RING_WIDTH, LOCATION_RING_Y + FireRing1->ReturnMemberBitMapHeight() };
		Ring2RectDown = { FireRing2->GetLocationX() - HITBOX_RING_WIDTH, LOCATION_RING_Y + FireRing2->ReturnMemberBitMapHeight() - HITBOX_RING_HEIGHT,
		FireRing2->GetLocationX() + HITBOX_RING_WIDTH, LOCATION_RING_Y + FireRing2->ReturnMemberBitMapHeight() };
		LittleRingRectDown = { LittleFireRing->GetLocationX() - HITBOX_RING_WIDTH, LOCATION_RING_Y + LittleFireRing->ReturnMemberBitMapHeight() - HITBOX_RING_HEIGHT,
			LittleFireRing->GetLocationX() + HITBOX_RING_WIDTH, LOCATION_RING_Y + LittleFireRing->ReturnMemberBitMapHeight() };

		if (IntersectRect(&TmpRect, &CharacterRect, &Ring1RectDown) || IntersectRect(&TmpRect, &CharacterRect, &Ring2RectDown) || IntersectRect(&TmpRect, &CharacterRect, &LittleRingRectDown))
		{
			return CRASHED_OBJECT;	//부딪친 것에 대해 참을 반환한다
		}
	}


	//점수 증가 부분
	if (User_Tmp >= FireRing1->GetLocationX() && User_Tmp <= FireRing1->GetLocationX() + MOVE_PIXEL && 
		CharacterYLocation <= LOCATION_RING_Y + FireRing1->ReturnMemberBitMapHeight() && true == FireRing1->ReturnScoreSwitch())
	{
 		Score_Tmp += SCORE_RING;
		FireRing1->SwitchOffScore();
	}
       	
	if (User_Tmp >= FireRing2->GetLocationX() && User_Tmp <= FireRing2->GetLocationX() + MOVE_PIXEL &&
		CharacterYLocation <= LOCATION_RING_Y + FireRing2->ReturnMemberBitMapHeight() && true == FireRing2->ReturnScoreSwitch())
	{
		Score_Tmp += SCORE_RING;
		FireRing2->SwitchOffScore();
	}

	if (User_Tmp >= LittleFireRing->GetLocationX() && User_Tmp <= LittleFireRing->GetLocationX() + MOVE_PIXEL &&
		CharacterYLocation <= LOCATION_RING_Y + LittleFireRing->ReturnMemberBitMapHeight() && true == LittleFireRing->ReturnScoreSwitch())
	{
		Score_Tmp += SCORE_RING;
		LittleFireRing->SwitchOffScore();
	}

	if (User_Tmp >= m_FireVector.at(Fire_Tmp)->GetLocationX() - LOCATION_CHARACTER_VERTICAL && User_Tmp <= m_FireVector.at(Fire_Tmp)->GetLocationX() + MOVE_PIXEL &&
		CharacterYLocation <= LOCATION_FIRE_Y + m_FireVector.at(Fire_Tmp)->ReturnMemberBitMapHeight() - LOCATION_CHARACTER_VERTICAL && true == m_FireVector.at(Fire_Tmp)->ReturnScoreSwitch())
	{
		Score_Tmp += SCORE_RING;
		m_FireVector.at(Fire_Tmp)->SwitchOffScore();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Score_Tmp; //넘어간 장애물 수에 따라 증가시켜야 할 점수 결정
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