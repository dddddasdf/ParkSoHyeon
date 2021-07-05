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
		TransparentBlt(MemDCBack, GetLocationX() - ReturnMemberBitMapWidth() - CharacterLocationX, LOCATION_RING_Y, ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
		break;
	case false:
		TransparentBlt(MemDCBack, GetLocationX() - CharacterLocationX, LOCATION_RING_Y, ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
		break;
	}

	m_IsLeft = !m_IsLeft;	//�� �������� ������ ��� �غ� ���� �¿� ���� ��� ���� ����

	m_DrawLocationApproach = GetLocationX() - CharacterLocationX;
}

void Ring1::DrawFinal(HDC MemDCBack, const int & WindowWidth)
{
	int XTmp = WindowWidth - (MAP_WIDTH - GetLocationX());

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
		TransparentBlt(MemDCBack, XTmp - ReturnMemberBitMapWidth(), LOCATION_RING_Y, ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
		break;
	case false:
		TransparentBlt(MemDCBack, XTmp, LOCATION_RING_Y, ReturnMemberBitMapWidth(),
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
	{
		SetLocationX(GetLocationX() + RING_BACK);
		m_IsGetScoreSwitch = true;
	}
}

void Ring1::RingMovingFinal(const int& MovePixel, const int& WindowWidth)
{
	SetLocationX(GetLocationX() - MovePixel);

	if (GetLocationX() < (MAP_WIDTH - WindowWidth) - 50)
	{
		SetLocationX(GetLocationX() + RING_BACK);
		m_IsGetScoreSwitch = true;
	}
}






LittleRing::LittleRing(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[HINDRANCE_LITTLERING_2 + 1];	//��ȣ ������ ���̼��� ���� 0���� �ƹ� �͵� ���� ����

	m_ObjectBitMap[HINDRANCE_LITTLERING_1] = ResourceMgr->ReturnLittleRingBitMapClass(HINDRANCE_LITTLERING_1);
	m_ObjectBitMap[HINDRANCE_LITTLERING_2] = ResourceMgr->ReturnLittleRingBitMapClass(HINDRANCE_LITTLERING_2);

	SetLocationX(X);
	SetLocationY(LOCATION_RING_Y);

	m_IsLeft = true;
	m_IsGetScoreSwitch = true;
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

	m_IsLeft = !m_IsLeft;	//�� �������� ������ ��� �غ� ���� �¿� ���� ��� ���� ����

	m_DrawLocationApproach = GetLocationX() - CharacterLocationX;
}

void LittleRing::DrawFinal(HDC MemDCBack, const int& WindowWidth)
{
	int XTmp = WindowWidth - (MAP_WIDTH - GetLocationX());

	switch (m_IsLeft)
	{
	case true:
	{
		m_BitMapNumberTmp = HINDRANCE_LITTLERING_1;
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, XTmp - ReturnMemberBitMapWidth(), LOCATION_RING_Y, ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
	}
	break;
	case false:
	{
		m_BitMapNumberTmp = HINDRANCE_LITTLERING_2;
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, XTmp, LOCATION_RING_Y, ReturnMemberBitMapWidth(),
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
	{
		SetLocationX(GetLocationX() + LITTLERING_BACK);
		m_IsGetScoreSwitch = true;
	}
}

void LittleRing::RingMovingFinal(const int& MovePixel, const int& WindowWidth)
{
	SetLocationX(GetLocationX() - MovePixel);

	if (GetLocationX() < (MAP_WIDTH - WindowWidth) - 50)
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
	
	m_BitMapNumberTmp = 0;

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

	//����ġ�� ���� ���� ���� ����Ѵ�
}

void Cash::DrawFinal(HDC MemDCBack, const int& WindowWidth)
{
	int XTmp = WindowWidth - (MAP_WIDTH - GetLocationX());

	switch (m_IsSwitchOn)
	{
	case true:
	{
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, XTmp - (ReturnMemberBitMapWidth() * 0.5), GetLocationY(), ReturnMemberBitMapWidth(),
			ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
	}
	break;
	case false:
		break;
	}

	//����ġ�� ���� ���� ���� ����Ѵ�
}


void Cash::CashMoving(const int& MovePixel, const int& CharacterLocationX)
{
	SetLocationX(GetLocationX() - MovePixel);

	if (GetLocationX() < CharacterLocationX - 50)
	{
		SetLocationX(GetLocationX() + LITTLERING_BACK);
		m_IsSwitchOn = true;	//����ġ�� ����
	}
}

void Cash::CashMovingFinal(const int& MovePixel, const int& WindowWidth)
{
	SetLocationX(GetLocationX() - MovePixel);

	if (GetLocationX() < (MAP_WIDTH - WindowWidth) - 50)
	{
		SetLocationX(GetLocationX() + LITTLERING_BACK);
		m_IsSwitchOn = true;
	}
}






MapTile::MapTile(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[BACKGROUND_CROWD_SECOND + 1];	//��ȣ ������ ���̼��� ���� 0���� �ƹ� �͵� ���� ����

	m_ObjectBitMap[BACKGROUND_FLOOR] = ResourceMgr->ReturnMapTileBitMapClass(BACKGROUND_FLOOR);
	m_ObjectBitMap[BACKGROUND_ELEPHANT] = ResourceMgr->ReturnMapTileBitMapClass(BACKGROUND_ELEPHANT);
	m_ObjectBitMap[BACKGROUND_CROWD_FIRST] = ResourceMgr->ReturnMapTileBitMapClass(BACKGROUND_CROWD_FIRST);
	m_ObjectBitMap[BACKGROUND_CROWD_SECOND] = ResourceMgr->ReturnMapTileBitMapClass(BACKGROUND_CROWD_SECOND);

	m_BitMapNumberTmp = BACKGROUND_FLOOR;
	int Tmp = ReturnMemberBitMapHeight();
	m_FloorYStart = HORIZON_HEIGHT - ReturnMemberBitMapHeight();	//�ٴ� Ÿ�� ���� Y��ǥ
	m_BitMapNumberTmp = BACKGROUND_CROWD_FIRST;
	m_CrowdYStart = HORIZON_HEIGHT - ReturnMemberBitMapHeight() - Tmp;	//���� Ÿ�� ���� Y��ǥ
	m_CrowdWidth = ReturnMemberBitMapWidth();
	m_CrowdHeight = ReturnMemberBitMapHeight();

	m_CrowdAnimation = false;
}

MapTile::~MapTile()
{
	delete[] m_ObjectBitMap;
}

void MapTile::Draw(HDC MemDCBack, const int& CharacterLocationX)
{
	//�ٴ�
	m_BitMapNumberTmp = BACKGROUND_FLOOR;
	for (int i = 0; i < 20; i++)
	{
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, ReturnMemberBitMapWidth() * i, m_FloorYStart, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(),
			m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
	}

	//����
	int StartBlock = CharacterLocationX / m_CrowdWidth;	//�÷��̾� ��ġ�� ���� ������ ���� ���ؾ� ��
	int CutWidth = CharacterLocationX - (m_CrowdWidth * StartBlock);	//�÷��̾��� �� X ��ǥ�� ���� �߸��� ĭ�� ���� ���

	m_StartBlockApproach = StartBlock;
	m_CutWidthApproach = CutWidth;
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

void MapTile::DrawFinal(HDC MemDCBack, const int& WindowWidth)
{
	//�ٴ�
	m_BitMapNumberTmp = BACKGROUND_FLOOR;
	for (int i = 0; i < 20; i++)
	{
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, ReturnMemberBitMapWidth() * i, m_FloorYStart, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(),
			m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
	}

	//����
	int Tmp = m_StartBlockApproach;	//������� ���� �������� �ʱ� ����
	for (int i = 0; i < 20; i++)
	{
		if (Tmp % 7 == 0)
			m_BitMapNumberTmp = BACKGROUND_ELEPHANT;
		else
			m_BitMapNumberTmp = BACKGROUND_CROWD_FIRST;

		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, -m_CutWidthApproach+ m_CrowdWidth * i, m_CrowdYStart, m_CrowdWidth, m_CrowdHeight,
			m_MemDC, 0, 0, m_CrowdWidth, m_CrowdHeight, RGB(255, 0, 255));

		Tmp++;
	}
}

void MapTile::DrawWin(HDC MemDCBack)
{	
	//����
	int Tmp = m_StartBlockApproach;	//������� ���� �������� �ʱ� ����

	for (int i = 0; i < 20; i++)
	{
		if (Tmp % 7 == 0)
			m_BitMapNumberTmp = BACKGROUND_ELEPHANT;
		else
		{
			switch (m_CrowdAnimation)
			{
			case false:
				m_BitMapNumberTmp = BACKGROUND_CROWD_FIRST;
				(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
				TransparentBlt(MemDCBack, -m_CutWidthApproach + m_CrowdWidth * i, m_CrowdYStart, m_CrowdWidth, m_CrowdHeight,
					m_MemDC, 0, 0, m_CrowdWidth, m_CrowdHeight, RGB(255, 0, 255));
				break;
			case true:
				m_BitMapNumberTmp = BACKGROUND_CROWD_SECOND;
				(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
				TransparentBlt(MemDCBack, -m_CutWidthApproach + m_CrowdWidth * i, m_CrowdYStart + 2, m_CrowdWidth, m_CrowdHeight,
					m_MemDC, 0, 0, m_CrowdWidth, m_CrowdHeight, RGB(255, 0, 255));
				break;
			}
		}
		Tmp++;
	}

	m_CrowdAnimation = !(m_CrowdAnimation);

	//�ٴ�
	m_BitMapNumberTmp = BACKGROUND_FLOOR;
	for (int i = 0; i < 20; i++)
	{
		(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
		TransparentBlt(MemDCBack, ReturnMemberBitMapWidth() * i, m_FloorYStart, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(),
			m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
	}
}





Character::Character(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[MOTION_DEAD + 1];	//��ȣ ������ ���̼��� ���� 0���� �ƹ� �͵� ���� ����

	for (int i = MOTION_STAND; i <= MOTION_DEAD; i++)
	{
		m_ObjectBitMap[i] = ResourceMgr->ReturnCharacterBitMapClass(i);
	}

	m_WinAnimation = false;
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

void Character::DrawCharacterFinal(HDC MemDCBack, const int& CharacterLocationX, const int& CharacterLocationY, const int& MotionNumber)
{
	m_BitMapNumberTmp = MotionNumber;
	(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
	TransparentBlt(MemDCBack, CharacterLocationX, CharacterLocationY - ReturnMemberBitMapHeight(), ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(),
		m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
}

void Character::DrawWin(HDC MemDCBack, const int& CharacterLocationX, const int& CharacterLocationY)
{
	switch (m_WinAnimation)
	{
	case false:
		m_BitMapNumberTmp = MOTION_WIN1;
		break;
	case true:
		m_BitMapNumberTmp = MOTION_WIN2;
		break;
	}
	
	(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
	TransparentBlt(MemDCBack, CharacterLocationX, CharacterLocationY - ReturnMemberBitMapHeight(), ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(),
		m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));

	m_WinAnimation = !m_WinAnimation;
}





Goal::Goal(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap;

	*m_ObjectBitMap = ResourceMgr->ReturnGoalBitMapClass();

	m_BitMapNumberTmp = 0;

	SetLocationX(LOCATION_GOAL_X - ReturnMemberBitMapWidth());
	SetLocationY(HORIZON_HEIGHT - ReturnMemberBitMapHeight());
}

Goal::~Goal()
{
	delete[] m_ObjectBitMap;
}

void Goal::Draw(HDC MemDCBack, const int& CharacterLocationX)
{
	(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
	TransparentBlt(MemDCBack, GetLocationX() - CharacterLocationX, GetLocationY(), ReturnMemberBitMapWidth(),
		ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));

	m_DrawLocationApproach = GetLocationX() - CharacterLocationX;
}

void Goal::DrawFinal(HDC MemDCBack, const int& WindowWidth)
{
	int XTmp = WindowWidth - (MAP_WIDTH - GetLocationX());

	(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());
	TransparentBlt(MemDCBack, m_DrawLocationApproach, GetLocationY(), ReturnMemberBitMapWidth(),
		ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));
}




Fire::Fire(HDC hdc, int X) : Object(hdc)
{
	m_ObjectBitMap = new BitMap[HINDRANCE_FIRE_2 + 1];	//��ȣ ������ ���̼��� ���� 0���� �ƹ� �͵� ���� ����

	m_ObjectBitMap[HINDRANCE_FIRE_1] = ResourceMgr->ReturnFireBitMapClass(HINDRANCE_FIRE_1);
	m_ObjectBitMap[HINDRANCE_FIRE_2] = ResourceMgr->ReturnFireBitMapClass(HINDRANCE_FIRE_2);

	m_BitMapNumberTmp = HINDRANCE_FIRE_1;

	SetLocationX(X);
	SetLocationY(LOCATION_FIRE_Y);

	m_AnimationState = HINDRANCE_FIRE_1;
	m_IsGetScoreSwitch = true;
}



Fire::~Fire()
{
	delete[] m_ObjectBitMap;
}

void Fire::Draw(HDC MemDCBack, const int& CharacterLocationX)
{
	switch (m_AnimationState)
	{
	case HINDRANCE_FIRE_1:
		{
			m_BitMapNumberTmp = HINDRANCE_FIRE_1;
			m_AnimationState = HINDRANCE_FIRE_2;
		}
		break;
	case HINDRANCE_FIRE_2:
		{
			m_BitMapNumberTmp = HINDRANCE_FIRE_2;
			m_AnimationState = HINDRANCE_FIRE_1;
		}
		break;
	}

	(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());

	TransparentBlt(MemDCBack, GetLocationX() - CharacterLocationX - LOCATION_CHARACTER_VERTICAL, LOCATION_FIRE_Y - ReturnMemberBitMapHeight(), ReturnMemberBitMapWidth(),
		ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));

	//ĳ���Ͱ� ȭ�θ� �������� ȭ�� ��ġ�� ������ ȭ�� ���� ����� �������� ȭ�ΰ� ��µǵ��� LOCATION_CHARACTER_VERTICAL�� ������

	m_DrawLocationApproach = GetLocationX() - CharacterLocationX - LOCATION_CHARACTER_VERTICAL;
}

void Fire::DrawFinal(HDC MemDCBack, const int& WindowWidth)
{
	int XTmp = WindowWidth - (MAP_WIDTH - GetLocationX()) - LOCATION_CHARACTER_VERTICAL;

	switch (m_AnimationState)
	{
	case HINDRANCE_FIRE_1:
	{
		m_BitMapNumberTmp = HINDRANCE_FIRE_1;
		m_AnimationState = HINDRANCE_FIRE_2;
	}
	break;
	case HINDRANCE_FIRE_2:
	{
		m_BitMapNumberTmp = HINDRANCE_FIRE_2;
		m_AnimationState = HINDRANCE_FIRE_1;
	}
	break;
	}

	(HBITMAP)SelectObject(m_MemDC, ReturnMemberBitmap());

	TransparentBlt(MemDCBack, m_DrawLocationApproach, LOCATION_FIRE_Y - ReturnMemberBitMapHeight(), ReturnMemberBitMapWidth(),
		ReturnMemberBitMapHeight(), m_MemDC, 0, 0, ReturnMemberBitMapWidth(), ReturnMemberBitMapHeight(), RGB(255, 0, 255));

	//ĳ���Ͱ� ȭ�θ� �������� ȭ�� ��ġ�� ������ ȭ�� ���� ����� �������� ȭ�ΰ� ��µǵ��� LOCATION_CHARACTER_VERTICAL�� ������
}
