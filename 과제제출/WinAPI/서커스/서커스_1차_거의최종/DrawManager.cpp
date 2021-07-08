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
	PointImage = ResourceMgr->ReturnPointBitMapClass();
	m_GameOverSelect = 0;

	//폰트 설정... - 점수용
	m_FontCustomize = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "돋움");

	//골 오브젝트 설정...
	GoalObject = new Goal(hdc, LOCATION_GOAL_X);

	//화로 클래스 배열(벡터0 초기화
	
	for (int i = 1; i < MAP_WIDTH / FIRE_DISTANCE; i++)
	{
		Fire *fire = new Fire(m_MemDCBack, FIRE_DISTANCE * i);
		m_FireVector.push_back(fire);
	}
	Fire* LastFire = new Fire(m_MemDCBack, NULL);	//골 앞에 있는 마지막 화로 설정
	LastFire->SetLocationX(LOCATION_GOAL_X - LastFire->ReturnMemberBitMapWidth() - LOCATION_CHARACTER_VERTICAL);
	m_FireVector.push_back(LastFire);
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
	//본 화면

	HBITMAP BitMapBack = CreateDIBSectionRe(hdc, m_WindowWidth, m_WindowHeight);
	HBITMAP OldBitMapBack = (HBITMAP)SelectObject(m_MemDCBack, BitMapBack);
	
	bool Tmp = m_WindowWidth >= MAP_WIDTH - CharacterXLocation + LOCATION_CHARACTER_VERTICAL;	//맵의 마지막 지점이 보이기 시작했는가?에 대한 여부

	switch (Tmp)
	{
	case false:
	{
		//배경 담당
		Map->Draw(m_MemDCBack, CharacterXLocation);

		//배경 그리는 파트 끝

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

			for (int i = 0; i <= 2; i++)
			{
				if ((m_FireVector.size()) > Tmp + i)
					(m_FireVector.at(Tmp + i))->Draw(m_MemDCBack, CharacterXLocation);	//마지막 화로가 되어서 다음 걸 참조할 수 없을 경우에 대해 예외처리
				else
					break;
			}
			//한 번에 3개만 출력하면 된다
		}

		//장애물 그리는 파트1 끝
		
		//골 그림
		GoalObject->Draw(m_MemDCBack, CharacterXLocation);

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

		
	}
		break;
	case true:
	{
		//배경 담당
		Map->DrawFinal(m_MemDCBack, m_WindowWidth);

		//배경 그리는 파트 끝

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//장애물 그리는 파트1 (불 고리 왼쪽 면, 화로)

		//불 고리 왼쪽 그림
		{
			FireRing1->DrawFinal(m_MemDCBack, m_WindowWidth);
			FireRing2->DrawFinal(m_MemDCBack, m_WindowWidth);
		}

		//작은 불 고리 왼쪽 그림
		{
			LittleFireRing->DrawFinal(m_MemDCBack, m_WindowWidth);
		}

		//돈주머니 그림 - m_IsCashSwitchOn이 true일 때만 그리는 함수를 실행한다
		{
			Cash1->DrawFinal(m_MemDCBack, m_WindowWidth);
		}

		//화로 그림
		{
			(m_FireVector.at(m_FireVector.size() - 2))->DrawFinal(m_MemDCBack, m_WindowWidth);
			(m_FireVector.at(m_FireVector.size() - 1))->DrawFinal(m_MemDCBack, m_WindowWidth);

			//맵의 마지막 부분에서는 화로가 두 개만 보일 수밖에 없으므로 사이즈 값을 이용해 인덱스를 찾아내면 된다
		}

		//장애물 그리는 파트1 끝

		//골 그림
		GoalObject->DrawFinal(m_MemDCBack, m_WindowWidth);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//캐릭터 그리는 파트

		int CharacterXTmp = m_WindowWidth - (MAP_WIDTH - CharacterXLocation);	//이 경우 전용 캐릭터 화면 표시 위치 임시 좌표
		CharacterObject->DrawCharacterFinal(m_MemDCBack, CharacterXTmp, CharacterYLocation, MotionNumber);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//장애물 그리는 파트2 (불 고리 오른쪽 면)

		//불 고리 오른쪽 그림
		{
			FireRing1->DrawFinal(m_MemDCBack, m_WindowWidth);
			FireRing2->DrawFinal(m_MemDCBack, m_WindowWidth);
		}

		//작은 불 고리 오른쪽 그림
		{
			LittleFireRing->DrawFinal(m_MemDCBack, m_WindowWidth);
		}

		//장애물 그리는 파트2 끝
	
	}
		break;
	}
	
	//장애물 담당 - 이었던 것 지금은 텍스트 출력용 임시
	HDC MemDCObstacle = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapObstacle;
	HBITMAP BitMapObstacle = NULL;

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
	SetTextAlign(m_MemDCBack, TA_CENTER);
	std::string str = std::to_string(Score);
	TextOut(m_MemDCBack, LOCATION_SCORE_X, LOCATION_SCORE_Y, str.c_str(), str.length());
	str = "Bonus: " + std::to_string(BonusScore);
	TextOut(m_MemDCBack, LOCATION_SCORE_X, LOCATION_BONUS_SCORE_Y, str.c_str(), str.length());
	

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
	bool Tmp = m_WindowWidth >= MAP_WIDTH - CharacterLocationX + LOCATION_CHARACTER_VERTICAL;	//맵의 마지막 지점이 보이기 시작했는가?에 대한 여부

	switch (Tmp)
	{
	case false:
	{
		FireRing1->RingMoving(MovingRingPixel, CharacterLocationX);
		FireRing2->RingMoving(MovingRingPixel, CharacterLocationX);
		LittleFireRing->RingMoving(MovingLittleRingPixel, CharacterLocationX);
		Cash1->CashMoving(MovingLittleRingPixel, CharacterLocationX);
	}
	break;
	case true:
	{
		FireRing1->RingMovingFinal(MovingRingPixel, m_WindowWidth);
		FireRing2->RingMovingFinal(MovingRingPixel, m_WindowWidth);
		LittleFireRing->RingMovingFinal(MovingLittleRingPixel, m_WindowWidth);
		Cash1->CashMovingFinal(MovingLittleRingPixel, m_WindowWidth);
	}
	break;
	}
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
	bool Tmp = m_WindowWidth >= MAP_WIDTH - CharacterXLocation + LOCATION_CHARACTER_VERTICAL;	//맵의 마지막 지점이 보이기 시작했는가?에 대한 여부

	switch (Tmp)
	{
	case false:
		CharacterRect = { CharacterXLocation + LOCATION_CHARACTER_VERTICAL, CharacterYLocation - CharacterObject->ReturnMemberBitMapHeight() + HITBOX_CHARACTER_HEIGHT_UP,
		CharacterXLocation + CharacterObject->ReturnMemberBitMapWidth() + (LONG)(LOCATION_CHARACTER_VERTICAL * 0.5f), CharacterYLocation - HITBOX_CHARACTER_HEIGHT_DOWN };	
		//화면에 보이는 유저 위치 보정 때문에 CHARACTER_LOCATION_X을 추가해줘야 함
		//↑유저 사각형
		break;
	case true:
		CharacterRect = { CharacterXLocation, CharacterYLocation - CharacterObject->ReturnMemberBitMapHeight() + HITBOX_CHARACTER_HEIGHT_UP,
		CharacterXLocation + CharacterObject->ReturnMemberBitMapWidth(), CharacterYLocation - HITBOX_CHARACTER_HEIGHT_DOWN };
		break;
	}

	int Score_Tmp = 0;	//넘은 장애물 수에 따라 보내줄 점수 임시
	int User_Tmp = CharacterXLocation + LOCATION_CHARACTER_VERTICAL + CharacterObject->ReturnMemberBitMapWidth() * 0.5f;	//판정을 위해 유저 캐릭터가 갖는 X좌표

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//화로와 부딪쳤는지 체크함
	int Fire_Tmp = CharacterXLocation / FIRE_DISTANCE;	//몇번째 화로부터 충돌 체크 해야 하는지 임시로 변수 구함
	//벡터 사이즈 넘어가면 오류 나므로... 체크하는 if 구문 필요
	{
		if (Fire_Tmp < m_FireVector.size())
		{
			RECT FireRectLeft = { m_FireVector.at(Fire_Tmp)->GetLocationX() + (m_FireVector.at(Fire_Tmp)->ReturnMemberBitMapWidth() * 0.5f) - HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL,
			LOCATION_FIRE_Y - HITBOX_FIRE_UP,
			m_FireVector.at(Fire_Tmp)->GetLocationX() + (m_FireVector.at(Fire_Tmp)->ReturnMemberBitMapWidth() * 0.5f) + HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL,
			LOCATION_FIRE_Y };

			if (IntersectRect(&TmpRect, &CharacterRect, &FireRectLeft))
			{
				return CRASHED_OBJECT;	//부딪친 것에 대해 참을 반환한다
			}
		}
		
		if (Fire_Tmp  + 1 < m_FireVector.size())
		{
			RECT FireRectRight = { m_FireVector.at(Fire_Tmp + 1)->GetLocationX() + (m_FireVector.at(Fire_Tmp + 1)->ReturnMemberBitMapWidth() * 0.5f) - HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL,
				LOCATION_FIRE_Y - HITBOX_FIRE_UP,
				m_FireVector.at(Fire_Tmp + 1)->GetLocationX() + (m_FireVector.at(Fire_Tmp + 1)->ReturnMemberBitMapWidth() * 0.5f) + HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL, LOCATION_FIRE_Y };

			if (IntersectRect(&TmpRect, &CharacterRect, &FireRectRight))
			{
				return CRASHED_OBJECT;	//부딪친 것에 대해 참을 반환한다
			}
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
	//고리1
	if (User_Tmp >= FireRing1->GetLocationX() && User_Tmp <= FireRing1->GetLocationX() + MOVE_PIXEL && 
		CharacterYLocation <= LOCATION_RING_Y + FireRing1->ReturnMemberBitMapHeight() && true == FireRing1->ReturnScoreSwitch())
	{
 		Score_Tmp += SCORE_RING;
		FireRing1->SwitchOffScore();
	}
       	
	//고리2
	if (User_Tmp >= FireRing2->GetLocationX() && User_Tmp <= FireRing2->GetLocationX() + MOVE_PIXEL &&
		CharacterYLocation <= LOCATION_RING_Y + FireRing2->ReturnMemberBitMapHeight() && true == FireRing2->ReturnScoreSwitch())
	{
		Score_Tmp += SCORE_RING;
		FireRing2->SwitchOffScore();
	}

	//작은 고리
	if (User_Tmp >= LittleFireRing->GetLocationX() && User_Tmp <= LittleFireRing->GetLocationX() + MOVE_PIXEL &&
		CharacterYLocation <= LOCATION_RING_Y + LittleFireRing->ReturnMemberBitMapHeight() && true == LittleFireRing->ReturnScoreSwitch())
	{
		Score_Tmp += SCORE_RING;
		LittleFireRing->SwitchOffScore();
	}

	//화로
	if (User_Tmp >= m_FireVector.at(Fire_Tmp)->GetLocationX() - LOCATION_CHARACTER_VERTICAL && User_Tmp <= m_FireVector.at(Fire_Tmp)->GetLocationX() + MOVE_PIXEL &&
		CharacterYLocation <= LOCATION_FIRE_Y + m_FireVector.at(Fire_Tmp)->ReturnMemberBitMapHeight() - LOCATION_CHARACTER_VERTICAL && true == m_FireVector.at(Fire_Tmp)->ReturnScoreSwitch())
	{
		Score_Tmp += SCORE_RING;
		m_FireVector.at(Fire_Tmp)->SwitchOffScore();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Score_Tmp; //넘어간 장애물 수에 따라 증가시켜야 할 점수 결정
}

bool DrawManager::IsInGoal_In(const int& CharacterXLocation, const int& CharacterYLocation)
{
	int User_Tmp = CharacterXLocation + LOCATION_CHARACTER_VERTICAL + CharacterObject->ReturnMemberBitMapWidth() * 0.5f;	//판정을 위해 유저 캐릭터가 갖는 X좌표
	
	if (User_Tmp >= GoalObject->GetLocationX() + (GoalObject->ReturnMemberBitMapWidth() * 0.5f) && 
		((User_Tmp >= GoalObject->GetLocationY() - JUMP_PIXEL * 0.5f) || User_Tmp <= GoalObject->GetLocationY() + JUMP_PIXEL * 0.5f))
	{
		
		return true;
	}

	return false;
}

void DrawManager::DrawWinImages(HDC hdc, const int& CharacterXLocation, const int& CharacterYLocation, const int& Life, const int& Score, const int& BonusScore, const int& MotionNumber)
{
	int CharacterXTmp = m_WindowWidth - (MAP_WIDTH - CharacterXLocation);	//이 경우 전용 캐릭터 화면 표시 위치 임시 좌표
	
	HBITMAP BitMapBack = CreateDIBSectionRe(hdc, m_WindowWidth, m_WindowHeight);
	HBITMAP OldBitMapBack = (HBITMAP)SelectObject(m_MemDCBack, BitMapBack);

	Map->DrawWin(m_MemDCBack);
	GoalObject->DrawFinal(m_MemDCBack, m_WindowWidth);
	CharacterObject->DrawWin(m_MemDCBack, CharacterXTmp, CharacterYLocation, MotionNumber);

	SelectObject(m_MemDCBack, m_FontCustomize);
	SetTextColor(m_MemDCBack, RGB(255, 255, 255));
	SetBkMode(m_MemDCBack, TRANSPARENT);
	SetTextAlign(m_MemDCBack, TA_CENTER);
	std::string str = std::to_string(Score);
	TextOut(m_MemDCBack, LOCATION_SCORE_X, LOCATION_SCORE_Y, str.c_str(), str.length());
	str = "Bonus: " + std::to_string(BonusScore);
	TextOut(m_MemDCBack, LOCATION_SCORE_X, LOCATION_BONUS_SCORE_Y, str.c_str(), str.length());

	
	if (0 == BonusScore)
	{
		SetTextAlign(m_MemDCBack, TA_LEFT);
		str = "스페이스바를 누르면 게임 종료";
		TextOut(m_MemDCBack, (m_WindowWidth * 0.5f) - (str.length() * 0.5f * 5), LOCATION_SCORE_Y + 20, str.c_str(), str.length());
	}

	BitBlt(hdc, 0, 0, m_WindowWidth, m_WindowHeight, m_MemDCBack, 0, 0, SRCCOPY);	//본 화면에 출력
	SelectObject(m_MemDCBack, OldBitMapBack);
	DeleteObject(BitMapBack);
}

void DrawManager::DrawGameOver(HDC hdc)
{
	HBITMAP BitMapBack = CreateDIBSectionRe(hdc, m_WindowWidth, m_WindowHeight);
	HBITMAP OldBitMapBack = (HBITMAP)SelectObject(m_MemDCBack, BitMapBack);
	
	SelectObject(m_MemDCBack, m_FontCustomize);
	SetTextColor(m_MemDCBack, RGB(255, 255, 255));
	SetBkMode(m_MemDCBack, TRANSPARENT);
	SetTextAlign(m_MemDCBack, TA_CENTER);
	std::string str = "게임 오버";
	TextOut(m_MemDCBack, (m_WindowWidth * 0.5f), 250, str.c_str(), str.length());
	str = "스페이스바를 누르면 게임 종료";
	TextOut(m_MemDCBack, (m_WindowWidth * 0.5f), 350, str.c_str(), str.length());

	BitBlt(hdc, 0, 0, m_WindowWidth, m_WindowHeight, m_MemDCBack, 0, 0, SRCCOPY);	//본 화면에 출력
	SelectObject(m_MemDCBack, OldBitMapBack);
	DeleteObject(BitMapBack);
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
	FireRing1->~Ring1();
	FireRing2->~Ring1();

	LittleFireRing->~LittleRing();

	Cash1->~Cash();

	Map->~MapTile();

	CharacterObject->~Character();

	GoalObject->~Goal();

	for (int i = 0; i < m_FireVector.size(); i++)
	{
		m_FireVector.at(i)->~Fire();
	}
}