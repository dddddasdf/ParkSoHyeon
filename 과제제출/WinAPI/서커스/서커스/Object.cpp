#include "Object.h"

Object::Object(HDC hdc)
{
	m_MemDC = CreateCompatibleDC(hdc);
}

Ring1::Ring1(HDC hdc, int X, int Y) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[HINDRANCE_RING_SECOND_2];

	m_ObjectBitMap[HINDRANCE_RING_FIRST_1] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_RING_FIRST_1);
	m_ObjectBitMap[HINDRANCE_RING_FIRST_2] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_RING_FIRST_2);
	m_ObjectBitMap[HINDRANCE_RING_SECOND_1] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_RING_SECOND_1);
	m_ObjectBitMap[HINDRANCE_RING_SECOND_2] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_RING_SECOND_2);

	SetLocationX(X);
	SetLocationY(Y);

	m_AnimationState = HINDRANCE_RING_FIRST_1;
}

Ring1::~Ring1()
{
	delete[] m_ObjectBitMap;
}

void Ring1::Draw(HDC MemDCBack, bool IsLeft)
{
	//IsLeft가 참으로 들어오면 왼쪽면 출력, 거짓으로 들어오면 오른쪽면 출력

	int BitMapNumberTmp;	//어떤 번호를 호출 시킬 것인지 저장하는 임시 변수

	//우선 현재 애니메이션이 어떤 건지 확인하고->그다음 왼쪽인지 오른쪽인지 확인하고->변수에 번호를 저장한 다음 미리 애니메이션 변수를 다음 걸로 교체해둔다

	switch (m_AnimationState)
	{
	case HINDRANCE_RING_FIRST_1:
	{
		if (true == IsLeft)
			BitMapNumberTmp = m_AnimationState = HINDRANCE_RING_FIRST_1;
		else
			BitMapNumberTmp = m_AnimationState = HINDRANCE_RING_FIRST_2;
	}
		
		m_AnimationState = HINDRANCE_RING_SECOND_1;
		break;
	case HINDRANCE_RING_SECOND_1:
	{
		if (true == IsLeft)
			BitMapNumberTmp = m_AnimationState = HINDRANCE_RING_SECOND_1;
		else
			BitMapNumberTmp = m_AnimationState = HINDRANCE_RING_SECOND_2;
	}
		
		m_AnimationState = HINDRANCE_RING_FIRST_1;
		break;
	}

	(HBITMAP)SelectObject(m_MemDC, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMap());

	switch (IsLeft)
	{
	case true:
		TransparentBlt(MemDCBack, GetLocationX() - m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapWidth(), RING_LOCATION_Y, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapWidth(), 
		m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapHeight(), m_MemDC, 0, 0, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapWidth(), m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapHeight(), RGB(255, 0, 255));
		break;
	case false:
		TransparentBlt(MemDCBack, GetLocationX(), RING_LOCATION_Y, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapWidth(),
			m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapHeight(), m_MemDC, 0, 0, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapWidth(), m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapHeight(), RGB(255, 0, 255));
		break;
	}
}