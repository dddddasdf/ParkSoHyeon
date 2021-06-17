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

void Ring1::Draw(HDC MemDCBack) 
{
	//m_IsLeft�� ���̸� ���ʸ� ���, �����̸� �����ʸ� ���

	int BitMapNumberTmp;	//� ��ȣ�� ȣ�� ��ų ������ �����ϴ� �ӽ� ����

	//�켱 ���� �ִϸ��̼��� � ���� Ȯ���ϰ�->�״��� �������� ���������� Ȯ���ϰ�->������ ��ȣ�� ������ ���� �̸� �ִϸ��̼� ������ ���� �ɷ� ��ü�صд�

	switch (m_AnimationState)
	{
	case HINDRANCE_RING_FIRST_1:
	{
		if (true == m_IsLeft)
			BitMapNumberTmp = HINDRANCE_RING_FIRST_1;
		else
			BitMapNumberTmp = HINDRANCE_RING_FIRST_2;
	}
		
		m_AnimationState = HINDRANCE_RING_SECOND_1;
		break;
	case HINDRANCE_RING_SECOND_1:
	{
		if (true == m_IsLeft)
			BitMapNumberTmp = HINDRANCE_RING_SECOND_1;
		else
			BitMapNumberTmp = HINDRANCE_RING_SECOND_2;
	}
		
		m_AnimationState = HINDRANCE_RING_FIRST_1;
		break;
	}

	(HBITMAP)SelectObject(m_MemDC, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMap());

	switch (m_IsLeft)
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

	m_IsLeft = !m_IsLeft;	//�� �������� ������ ����� �� �غ� �Ѵ�
}

void Ring1::MoveXPixel(int MovePixel, int CharacterLocationX)
{
	//�� �� X ��ǥ �����ϴ� �κ�

	SetLocationX(GetLocationX() - MovePixel);

	if (GetLocationX() < CharacterLocationX - 50)
		SetLocationX(GetLocationX() + 1200);
}







LittleRing::LittleRing(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[HINDRANCE_LITTLERING_2 + 1];	//��ȣ ������ ���̼��� ���� 0���� �ƹ� �͵� ���� ����

	m_ObjectBitMap[HINDRANCE_LITTLERING_1] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_LITTLERING_1);
	m_ObjectBitMap[HINDRANCE_LITTLERING_2] = ResourceMgr->ReturnRingBitMapClass(HINDRANCE_LITTLERING_2);

	SetLocationX(X);

	m_IsLeft = true;
}

void LittleRing::Draw(HDC MemDCBack)
{
	//m_IsLeft�� ���̸� ���ʸ� ���, �����̸� �����ʸ� ���

	int BitMapNumberTmp;	//� ��ȣ�� ȣ�� ��ų ������ �����ϴ� �ӽ� ����

	//�������� ���������� Ȯ���ϰ�->������ ��ȣ�� ����

	switch (m_IsLeft)
	{
	case true:
	{
		BitMapNumberTmp = HINDRANCE_LITTLERING_1;
		(HBITMAP)SelectObject(m_MemDC, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMap());
		TransparentBlt(MemDCBack, GetLocationX() - m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapWidth(), RING_LOCATION_Y, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapWidth(),
			m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapHeight(), m_MemDC, 0, 0, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapWidth(), m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapHeight(), RGB(255, 0, 255));
	}
	break;
	case false:
	{
		BitMapNumberTmp = HINDRANCE_LITTLERING_2;
		(HBITMAP)SelectObject(m_MemDC, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMap());
		TransparentBlt(MemDCBack, GetLocationX(), RING_LOCATION_Y, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapWidth(),
			m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapHeight(), m_MemDC, 0, 0, m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapWidth(), m_ObjectBitMap[BitMapNumberTmp].ReturnBitMapHeight(), RGB(255, 0, 255));
	}
	break;
	}

	m_IsLeft = !m_IsLeft;	//�� �������� ������ ����� �� �غ� �Ѵ�
}

void LittleRing::MoveXPixel(int MovePixel, int CharacterLocationX)
{
	//�� �� X ��ǥ �����ϴ� �κ�

	SetLocationX(GetLocationX() - MovePixel);

	if (GetLocationX() < CharacterLocationX - 50)
		SetLocationX(GetLocationX() + 2500);
}

LittleRing::~LittleRing()
{
	delete[] m_ObjectBitMap;
}