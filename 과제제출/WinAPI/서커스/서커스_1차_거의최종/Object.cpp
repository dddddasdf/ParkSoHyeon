#include "Object.h"

Object::Object(HDC hdc)
{
	m_MemDC = CreateCompatibleDC(hdc);
}

Ring1::Ring1(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[HINDRANCE_RING_SECOND_2 + 1];	//번호 관리의 용이성을 위해 0번은 아무 것도 없는 더미

	m_ObjectBitMap[HINDRANCE_RING_FIRST_1] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_RING_FIRST_1);
	m_ObjectBitMap[HINDRANCE_RING_FIRST_2] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_RING_FIRST_2);
	m_ObjectBitMap[HINDRANCE_RING_SECOND_1] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_RING_SECOND_1);
	m_ObjectBitMap[HINDRANCE_RING_SECOND_2] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_RING_SECOND_2);

	SetLocationX(X);
	SetLocationY(LOCATION_RING_Y);

	m_AnimationState = HINDRANCE_RING_FIRST_1;
	m_IsLeft = true;
	m_IsGetScoreSwitch = true;
}

Ring1::~Ring1()
{
	delete[] m_ObjectBitMap;
}

void Ring1::Draw(HDC MemDCBack, const int& CharacterLocationX) 
{
	//m_IsLeft가 참이면 왼쪽면 출력, 거짓이면 오른쪽면 출력
	//우선 현재 애니메이션이 어떤 건지 확인하고->그다음 왼쪽인지 오른쪽인지 확인하고->오른쪽일 경우 애니메이션 구분 변수에 번호를 저장한 다음 미리 애니메이션 변수를 다음 걸로 교체해둔다

	switch (m_AnimationState)
	{
	case HINDRANCE_RING_FIRST_1:
	{
		if (true == m_IsLeft)
			m_BitMapNumberTmp = HINDRANCE_RING_FIRST_1;
		else
		{
			m_BitMapNumberTmp = HINDRANCE_RING_FIRST_2;
			m_AnimationState = HINDRANCE_RING_SECOND_1;
		}
	}
		break;
	case HINDRANCE_RING_SECOND_1:
	{
		if (true == m_IsLeft)
			m_BitMapNumberTmp = HINDRANCE_RING_SECOND_1;
		else
		{
			m_BitMapNumberTmp = HINDRANCE_RING_SECOND_2;
			m_AnimationState = HINDRANCE_RING_FIRST_1;
		}
	}
		break;
	}

	(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());

	switch (m_IsLeft)
	{
	case true:
		TransparentBlt(MemDCBack, GetLocationX() - ReturnMemberBitMapWidth() - CharacterLocationX, LOCATION_RING_Y, ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
		break;
	case false:
		TransparentBlt(MemDCBack, GetLocationX() - CharacterLocationX, LOCATION_RING_Y, ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
		break;
	}

	m_IsLeft = !m_IsLeft;	//다 끝났으니 다음면 출력 준비를 위해 좌우 구분 멤버 변수 반전
}

void Ring1::RingMoving(const int& MovePixel, const int& CharacterLocationX)
{
	//불 고리 X 좌표 변경하는 부분

	SetLocationX(GetLocationX() - MovePixel);

	if (GetLocationX() < CharacterLocationX - 50)
	{
		SetLocationX(GetLocationX() + RING_BACK);
		m_IsGetScoreSwitch = true;
	}
}







LittleRing::LittleRing(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[HINDRANCE_LITTLERING_2 + 1];	//번호 관리의 용이성을 위해 0번은 아무 것도 없는 더미

	m_ObjectBitMap[HINDRANCE_LITTLERING_1] = ResourceMgr->ReturnLittleRingBitMapClass(HINDRANCE_LITTLERING_1);
	m_ObjectBitMap[HINDRANCE_LITTLERING_2] = ResourceMgr->ReturnLittleRingBitMapClass(HINDRANCE_LITTLERING_2);

	SetLocationX(X);
	SetLocationY(LOCATION_RING_Y);

	m_IsLeft = true;
	m_IsGetScoreSwitch = true;
}

void LittleRing::Draw(HDC MemDCBack, const int& CharacterLocationX)
{
	//m_IsLeft가 참이면 왼쪽면 출력, 거짓이면 오른쪽면 출력

	//왼쪽인지 오른쪽인지 확인하고->변수에 번호를 저장

	switch (m_IsLeft)
	{
	case true:
	{
		m_BitMapNumberTmp = HINDRANCE_LITTLERING_1;
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, GetLocationX() - ReturnMemberBitMapWidth() - CharacterLocationX, LOCATION_RING_Y, ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
	}
	break;
	case false:
	{
		m_BitMapNumberTmp = HINDRANCE_LITTLERING_2;
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, GetLocationX() - CharacterLocationX, LOCATION_RING_Y, ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
	}
	break;
	}

	m_IsLeft = !m_IsLeft;	//다 끝났으니 다음면 출력 준비를 위해 좌우 구분 멤버 변수 반전
}

void LittleRing::RingMoving(const int& MovePixel, const int& CharacterLocationX)
{
	//불 고리 X 좌표 변경하는 부분

	SetLocationX(GetLocationX() - MovePixel);

	if (GetLocationX() < CharacterLocationX - 50)
	{
		SetLocationX(GetLocationX() + LITTLERING_BACK);
		m_IsGetScoreSwitch = true;
	}
}

LittleRing::~LittleRing()
{
	delete[] m_ObjectBitMap;
}






Cash::Cash(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap;

	*m_ObjectBitMap = ResourceMgr->ReturnCashBitMapClass();

	SetLocationX(X);
	SetLocationY(LOCATION_RING_Y + 25);
	
	m_IsSwitchOn = true;
}

Cash::~Cash()
{
	delete[] m_ObjectBitMap;
}

void Cash::Draw(HDC MemDCBack, const int& CharacterLocationX)
{
	switch (m_IsSwitchOn)
	{
	case true:
	{
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, GetLocationX() - (ReturnMemberBitMapWidth() * 0.5) - CharacterLocationX, GetLocationY(), ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
	}
		break;
	case false:
		break;
	}

	//스위치가 켜져 있을 때만 출력한다
}

void Cash::CashMoving(const int& MovePixel, const int& CharacterLocationX)
{
	SetLocationX(GetLocationX() - MovePixel);

	if (GetLocationX() < CharacterLocationX - 50)
	{
		SetLocationX(GetLocationX() + LITTLERING_BACK);
		m_IsSwitchOn = true;	//스위치도 켜줌
	}
}






MapTile::MapTile(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[BACKGROUND_CROWD_SECOND + 1];	//번호 관리의 용이성을 위해 0번은 아무 것도 없는 더미

	m_ObjectBitMap[BACKGROUND_FLOOR] = ResourceMgr->ReturnMapTileBitMapClass(BACKGROUND_FLOOR);
	m_ObjectBitMap[BACKGROUND_ELEPHANT] = ResourceMgr->ReturnMapTileBitMapClass(BACKGROUND_ELEPHANT);
	m_ObjectBitMap[BACKGROUND_CROWD_FIRST] = ResourceMgr->ReturnMapTileBitMapClass(BACKGROUND_CROWD_FIRST);
	m_ObjectBitMap[BACKGROUND_CROWD_SECOND] = ResourceMgr->ReturnMapTileBitMapClass(BACKGROUND_CROWD_SECOND);

	m_BitMapNumberTmp = BACKGROUND_FLOOR;
	int Tmp = ReturnMemberBitMapHeight();
	m_FloorYStart = HORIZON_HEIGHT - ReturnMemberBitMapHeight();	//바닥 타일 시작 Y좌표
	m_BitMapNumberTmp = BACKGROUND_CROWD_FIRST;
	m_CrowdYStart = HORIZON_HEIGHT - ReturnMemberBitMapHeight() - Tmp;	//관중 타일 시작 Y좌표
	m_CrowdWidth = ReturnMemberBitMapWidth();
	m_CrowdHeight = ReturnMemberBitMapHeight();
}

MapTile::~MapTile()
{
	delete[] m_ObjectBitMap;
}

void MapTile::Draw(HDC MemDCBack, const int& CharacterLocationX)
{
	//바닥
	m_BitMapNumberTmp = BACKGROUND_FLOOR;
	for (int i = 0; i < 20; i++)
	{
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, ReturnMemberBitMapWidth() * i, m_FloorYStart, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(),
			m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
	}

	//군중
	int StartBlock = CharacterLocationX / m_CrowdWidth;	//플레이어 위치에 따라 시작할 블럭을 정해야 함
	int CutWidth = CharacterLocationX - (m_CrowdWidth * StartBlock);	//플레이어의 맵 X 좌표에 따라 잘리는 칸의 길이 계산
	for (int i = 0; i < 20; i++)
	{
		if (StartBlock % 7 == 0)
			m_BitMapNumberTmp = BACKGROUND_ELEPHANT;
		else
			m_BitMapNumberTmp = BACKGROUND_CROWD_FIRST;
		
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, -CutWidth + m_CrowdWidth * i, m_CrowdYStart, m_CrowdWidth, m_CrowdHeight,
			m_MemDC, 0, 0, m_CrowdWidth, m_CrowdHeight, RGB(255, 0, 255));

		StartBlock++;
	}
}



Character::Character(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[MOTION_DEAD + 1];	//번호 관리의 용이성을 위해 0번은 아무 것도 없는 더미

	for (int i = MOTION_STAND; i <= MOTION_DEAD; i++)
	{
		m_ObjectBitMap[i] = ResourceMgr->ReturnCharacterBitMapClass(i);
	}
}

Character::~Character()
{
	delete[] m_ObjectBitMap;
}

void Character::DrawChracater(HDC MemDCBack, const int& CharacterLocationY, const int& MotionNumber)
{
	m_BitMapNumberTmp = MotionNumber;
	(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
	TransparentBlt(MemDCBack, LOCATION_CHARACTER_VERTICAL, CharacterLocationY - ReturnMemberBitMapHeight(), ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), 
		m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
}




Goal::Goal(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap;

	*m_ObjectBitMap = ResourceMgr->ReturnGoalBitMapClass();

	SetLocationX(LOCATION_GOAL_X);
	SetLocationY(HORIZON_HEIGHT);
}

Goal::~Goal()
{
	delete[] m_ObjectBitMap;
}




Fire::Fire(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[HINDRANCE_FIRE_2 + 1];	//번호 관리의 용이성을 위해 0번은 아무 것도 없는 더미

	m_ObjectBitMap[HINDRANCE_FIRE_1] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_FIRE_1);
	m_ObjectBitMap[HINDRANCE_FIRE_2] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_FIRE_2);

	SetLocationX(X);
	SetLocationY(LOCATION_RING_Y);

	m_AnimationState = HINDRANCE_RING_FIRST_1;
	m_IsGetScoreSwitch = true;
}



Fire::~Fire()
{
	delete[] m_ObjectBitMap;
}

void Fire::Draw(HDC MemDCBack, const int& CharacterLocationY)
{

}