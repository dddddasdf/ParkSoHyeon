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

	m_AnimationState = HINDRANCE_RING_FIRST_1;
	m_IsLeft = true;
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
		TransparentBlt(MemDCBack, GetLocationX() - ReturnMemberBitMapWidth() - CharacterLocationX, RING_LOCATION_Y, ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
		break;
	case false:
		TransparentBlt(MemDCBack, GetLocationX() - CharacterLocationX, RING_LOCATION_Y, ReturnMemberBitMapWidth(),
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
		SetLocationX(GetLocationX() + RING_BACK);
}







LittleRing::LittleRing(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[HINDRANCE_LITTLERING_2 + 1];	//번호 관리의 용이성을 위해 0번은 아무 것도 없는 더미

	m_ObjectBitMap[HINDRANCE_LITTLERING_1] = ResourceMgr->ReturnLittleRingBitMapClass(HINDRANCE_LITTLERING_1);
	m_ObjectBitMap[HINDRANCE_LITTLERING_2] = ResourceMgr->ReturnLittleRingBitMapClass(HINDRANCE_LITTLERING_2);

	SetLocationX(X);

	m_IsLeft = true;
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
		TransparentBlt(MemDCBack, GetLocationX() - ReturnMemberBitMapWidth() - CharacterLocationX, RING_LOCATION_Y, ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
	}
	break;
	case false:
	{
		m_BitMapNumberTmp = HINDRANCE_LITTLERING_2;
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, GetLocationX() - CharacterLocationX, RING_LOCATION_Y, ReturnMemberBitMapWidth(),
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
		SetLocationX(GetLocationX() + LITTLERING_BACK);
}

LittleRing::~LittleRing()
{
	delete[] m_ObjectBitMap;
}