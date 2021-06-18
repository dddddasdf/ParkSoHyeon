#include "Object.h"

Object::Object(HDC hdc)
{
	m_MemDC = CreateCompatibleDC(hdc);
}

Ring1::Ring1(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[HINDRANCE_RING_SECOND_2 + 1];	//��ȣ ������ ���̼��� ���� 0���� �ƹ� �͵� ���� ����

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
	//m_IsLeft�� ���̸� ���ʸ� ���, �����̸� �����ʸ� ���
	//�켱 ���� �ִϸ��̼��� � ���� Ȯ���ϰ�->�״��� �������� ���������� Ȯ���ϰ�->�������� ��� �ִϸ��̼� ���� ������ ��ȣ�� ������ ���� �̸� �ִϸ��̼� ������ ���� �ɷ� ��ü�صд�

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

	m_IsLeft = !m_IsLeft;	//�� �������� ������ ��� �غ� ���� �¿� ���� ��� ���� ����
}

void Ring1::RingMoving(const int& MovePixel, const int& CharacterLocationX)
{
	//�� �� X ��ǥ �����ϴ� �κ�

	SetLocationX(GetLocationX() - MovePixel);

	if (GetLocationX() < CharacterLocationX - 50)
		SetLocationX(GetLocationX() + RING_BACK);
}







LittleRing::LittleRing(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[HINDRANCE_LITTLERING_2 + 1];	//��ȣ ������ ���̼��� ���� 0���� �ƹ� �͵� ���� ����

	m_ObjectBitMap[HINDRANCE_LITTLERING_1] = ResourceMgr->ReturnLittleRingBitMapClass(HINDRANCE_LITTLERING_1);
	m_ObjectBitMap[HINDRANCE_LITTLERING_2] = ResourceMgr->ReturnLittleRingBitMapClass(HINDRANCE_LITTLERING_2);

	SetLocationX(X);

	m_IsLeft = true;
}

void LittleRing::Draw(HDC MemDCBack, const int& CharacterLocationX)
{
	//m_IsLeft�� ���̸� ���ʸ� ���, �����̸� �����ʸ� ���

	//�������� ���������� Ȯ���ϰ�->������ ��ȣ�� ����

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

	m_IsLeft = !m_IsLeft;	//�� �������� ������ ��� �غ� ���� �¿� ���� ��� ���� ����
}

void LittleRing::RingMoving(const int& MovePixel, const int& CharacterLocationX)
{
	//�� �� X ��ǥ �����ϴ� �κ�

	SetLocationX(GetLocationX() - MovePixel);

	if (GetLocationX() < CharacterLocationX - 50)
		SetLocationX(GetLocationX() + LITTLERING_BACK);
}

LittleRing::~LittleRing()
{
	delete[] m_ObjectBitMap;
}