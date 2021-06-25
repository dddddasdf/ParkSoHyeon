#include "DrawManager.h"

#define TEST_LOCATION 500	//�׽�Ʈ�� �� �ӽ� ��ǥ

void DrawManager::Init(HWND hWnd, HDC hdc)
{
	//������ ũ�� ���ؼ� ������ ��� ������ �־�α�
	RECT WindowRect;
	GetWindowRect(hWnd, &WindowRect);
	m_WindowWidth = WindowRect.right - WindowRect.left;
	m_WindowHeight = WindowRect.bottom - WindowRect.top;

	m_MemDCBack = CreateCompatibleDC(hdc);	//��� ������ �ִ� DC ����


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//������Ʈ Ŭ���� �ʱ�ȭ

	FireRing1 = new Ring1(hdc, DEFAULT_RING1_START);
	FireRing2 = new Ring1(hdc, DEFAULT_RING2_START);
	LittleFireRing = new LittleRing(hdc, DEFAULT_LITTLERING_START);
	Cash1 = new Cash(hdc, DEFAULT_LITTLERING_START);
	Map = new MapTile(hdc, NULL);
	CharacterObject = new Character(hdc, NULL);


	//������ ��Ʈ�� �޾Ƶα�...

	LifeImage = ResourceMgr->ReturnInterfaceBitMapClass(2);


	////////////////////�Ʒ���� �� ���� ����

	
	{
		//�� �̹��� ������ �̸� ���س���
		HBITMAP HBitmapTmp;
		BITMAP BitmapTmp;

		HBitmapTmp = ResourceMgr->ReturnBackgroundImage(BACKGROUND_FLOOR);
		GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);



		HBitmapTmp = ResourceMgr->ReturnObstacleImage(OBSTACLE_FIRE_1);
		GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);

		m_FireSizeWidth = BitmapTmp.bmWidth;
		m_FireSizeHeight = BitmapTmp.bmHeight;	//ȭ�� ������
	}


	{
		////ȭ�� X��ǥ ���� ����
		//if (!m_ObstacleFireXLocation.empty())
		//	m_ObstacleFireXLocation.clear();	//�̰� ���� �� ���� ����
		//
		//for (int i = FIRE_DISTANCE; i <= END_OF_MAP; i += FIRE_DISTANCE)
		//	m_ObstacleFireXLocation.push_back(i);	//ȭ�δ� 500�ȼ� �������� ��ġ�Ǿ� �ִ�

		m_FireAnimation = OBSTACLE_FIRE_1;	//����� ȭ�� �ִϸ��̼��� ���� ��������� �ʱ�ȭ
	}
}

void DrawManager::DeadInit()
{
	//X��ǥ�� ó�� ��ġ�� �ǵ��� �ָ� �ȴ�

	FireRing1->SetLocationX(DEFAULT_RING1_START);
	FireRing2->SetLocationX(DEFAULT_RING2_START);
	LittleFireRing->SetLocationX(DEFAULT_LITTLERING_START);
	Cash1->SetLocationX(DEFAULT_LITTLERING_START);
	Cash1->SwitchOnCash();
}

void DrawManager::DrawImages(HDC hdc, const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation, const int& Life, const int& Score)
{	
	//�� ȭ��
	
	HBITMAP BitMapBack = CreateDIBSectionRe(hdc, m_WindowWidth, m_WindowHeight);
	HBITMAP OldBitMapBack = (HBITMAP)SelectObject(m_MemDCBack, BitMapBack);

	BITMAP BitMapImageSize;	//�̹��� ���� ũ�⸦ ���ϱ� ���� ��Ʈ��

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��� ���
	Map->Draw(m_MemDCBack, CharacterXLocation);

	//��� �׸��� ��Ʈ ��

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��ֹ� ���
	HDC MemDCObstacle = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapObstacle;
	HBITMAP BitMapObstacle = NULL;

	//��ֹ� �׸��� ��Ʈ1 (�� �� ���� ��, ȭ��)

	//�� �� ���� �׸�
	{
		FireRing1->Draw(m_MemDCBack, CharacterXLocation);
		FireRing2->Draw(m_MemDCBack, CharacterXLocation);		
	}

	//���� �� �� ���� �׸�
	{
		LittleFireRing->Draw(m_MemDCBack, CharacterXLocation);
	}

	//���ָӴ� �׸� - m_IsCashSwitchOn�� true�� ���� �׸��� �Լ��� �����Ѵ�
	{
		Cash1->Draw(m_MemDCBack, CharacterXLocation);
	}

	//ȭ�� �׸�
	{
		switch (m_FireAnimation)
		{
		case OBSTACLE_FIRE_1:
			BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_FIRE_1);
			m_FireAnimation = OBSTACLE_FIRE_2;	//��Ʈ���� �޾ƿ� ���� �ִϸ��̼� ���� ������ �̸� ���� �ɷ� ��ü�ؼ� ���� ������ ��� �� �ٷιٷ� ����� ������ �ǵ��� �Ѵ�
			break;
		case OBSTACLE_FIRE_2:
			BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_FIRE_2);
			m_FireAnimation = OBSTACLE_FIRE_1;
			break;
		}

		OlbBitMapObstacle = (HBITMAP)SelectObject(MemDCObstacle, BitMapObstacle);

		for (int i = FIRE_DISTANCE - (CharacterXLocation % FIRE_DISTANCE) - 40; i <= m_WindowWidth; i += FIRE_DISTANCE)
		{
			//���� �������� ȭ�� ���
			/*
			������ �ʿ����� X��ǥ�� �������� ����ϰԲ� �Ѵ�. ȭ�δ� ������������ 600 �������� ������ �ִ�... ������ ��ġ�� ȭ�� �������� ���� ���������� ���� ���� ȭ�α����� �Ÿ��� ���Ͽ�
			����Ѵ�

			-40�� �ִ� ����: ���� ���ʿ� �ִ� ȭ�ε� ������ ����ϱ� ���ؼ�
			*/

			TransparentBlt(m_MemDCBack, i, HORIZON_FIRE - m_FireSizeWidth, m_FireSizeWidth, m_FireSizeHeight, MemDCObstacle, 0, 0, m_FireSizeWidth, m_FireSizeHeight, RGB(255, 0, 255));
		}
	}

	//��ֹ� �׸��� ��Ʈ1 ��

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ĳ���� �׸��� ��Ʈ

	CharacterObject->DrawChracater(m_MemDCBack, CharacterYLocation, MotionNumber);

	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��ֹ� �׸��� ��Ʈ2 (�� �� ������ ��)
	
	//�� �� ������ �׸�
	{
		FireRing1->Draw(m_MemDCBack, CharacterXLocation);
		FireRing2->Draw(m_MemDCBack, CharacterXLocation);
	}

	//���� �� �� ������ �׸�
	{
		LittleFireRing->Draw(m_MemDCBack, CharacterXLocation);
	}


	SelectObject(MemDCObstacle, OlbBitMapObstacle);

	//��ֹ� �׸��� ��Ʈ2 ��

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//����, ��� ���

	for (int i = Life; i > 0; i--)
	{
		(HBITMAP)SelectObject(MemDCObstacle, LifeImage.ReturnBitMap());
		TransparentBlt(m_MemDCBack, LIFE_LOCATION_X - LifeImage.ReturnBitMapWidth() * i, LIFE_LOCATION_Y, LifeImage.ReturnBitMapWidth(), LifeImage.ReturnBitMapHeight(), 
			MemDCObstacle, 0, 0, LifeImage.ReturnBitMapWidth(), LifeImage.ReturnBitMapHeight(), RGB(255, 0, 255));
	}

	SetTextAlign(m_MemDCBack, TA_LEFT);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	BitBlt(hdc, 0, 0, m_WindowWidth, m_WindowHeight, m_MemDCBack, 0, 0, SRCCOPY);	//�� ȭ�鿡 ���
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
	//���ָӴϿ� �ε��ƴ��� üũ��
	//���ָӴϰ� �� �Ǿ����� ���� üũ�ϸ� �ȴ�... �Ծ ���� ���ȿ��� ���� �������� ���ǹ�
	if (Cash1->ReturnIsCashSwitched())
	{
		
		RECT TmpRect;
		RECT CharacterRect = { (CharacterXLocation + CHARACTER_LOCATION_X) + (CharacterObject->ReturnMemberBitMapWidth() * 0.5) - HITBOX_CHARACTER_WIDTH, CharacterYLocation - HITBOX_CHARACTER_HEIGHT_UP,
			(CharacterXLocation + CHARACTER_LOCATION_X) + (CharacterObject->ReturnMemberBitMapWidth() * 0.5) + HITBOX_CHARACTER_WIDTH, CharacterYLocation - HITBOX_CHARACTER_HEIGHT_DOWN };
		//ȭ�鿡 ���̴� ���� ��ġ ���� ������ CHARACTER_LOCATION_X�� �߰������ ��
		//������ �簢��
		
		RECT CashRect = { Cash1->GetLocationX() - (Cash1->ReturnMemberBitMapWidth() * 0.5f), Cash1->GetLocationY(),
			Cash1->GetLocationX() + (Cash1->ReturnMemberBitMapWidth() * 0.5f), Cash1->GetLocationY() + Cash1->ReturnMemberBitMapHeight() };

		if (IntersectRect(&TmpRect, &CharacterRect, &CashRect))
		{
			Cash1->SwitchOffCash();	//�ε������� ���ָӴ� ����ġ ����
			return true;
		}
	}
	return false;	//�ƹ� �ϵ� �������� false ��ȯ
}

bool DrawManager::IsObsjectCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation)
{
	RECT TmpRect;
	RECT CharacterRect = { CharacterXLocation + CHARACTER_LOCATION_X, CharacterYLocation - CharacterObject->ReturnMemberBitMapHeight(),
		CharacterXLocation + CharacterObject->ReturnMemberBitMapWidth() + CHARACTER_LOCATION_X * 0.5f, CharacterYLocation };	//ȭ�鿡 ���̴� ���� ��ġ ���� ������ CHARACTER_LOCATION_X�� �߰������ ��
	//������ �簢��

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ȭ�ο� �ε��ƴ��� üũ��
	//{
	//	int FireXLocation = FIRE_DISTANCE - (CharacterXLocation % FIRE_DISTANCE) - 40 + CharacterXLocation - m_FireSizeWidth + 25;

	//	RECT FireRectLeft = { FireXLocation, HORIZON_FIRE - m_FireSizeHeight + 10, FireXLocation + m_FireSizeWidth - 15, HORIZON_FIRE };
	//	RECT FireRectRight = { FireXLocation + FIRE_DISTANCE, HORIZON_FIRE - m_FireSizeHeight + 10, (FireXLocation + FIRE_DISTANCE) + m_FireSizeWidth - 15, HORIZON_FIRE };
	//	//���װ� �ƴ� �̻� ���� ���� �ι�° ȭ�ο� �ε�ĥ ���� �����Ƿ� ���� ������ ȭ�� �ϳ� �������� ȭ�� �ϳ��� üũ�ϸ� ������ ��
	//	//���� �ʹ� ������ ��� ���ݾ� ���°��� �������ִ� ����...

	//	if (IntersectRect(&TmpRect, &CharacterRect, &FireRectLeft))
	//	{
	//		return true;	//�ε�ģ �Ϳ� ���� ���� ��ȯ�Ѵ�
	//	}
	//	if (IntersectRect(&TmpRect, &PlayerRect, &FireRectRight))
	//	{
	//		return true;	//�ε�ģ �Ϳ� ���� ���� ��ȯ�Ѵ�
	//	}
	//}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//���� �ε��ƴ��� üũ��
	//���� ���κ� �Ʒ��κ����� �ɰ��� �� �Ѱ� �ε��ƴ��� üũ�Ѵ�
	{
		RECT Ring1RectDown = { FireRing1->GetLocationX() - HITBOX_RING_WIDTH, RING_LOCATION_Y + FireRing1->ReturnMemberBitMapHeight() - HITBOX_RING_HEIGHT,
			FireRing1->GetLocationX() + HITBOX_RING_WIDTH, RING_LOCATION_Y + FireRing1->ReturnMemberBitMapHeight() };
		RECT Ring2RectDown = { FireRing2->GetLocationX() - HITBOX_RING_WIDTH, RING_LOCATION_Y + FireRing2->ReturnMemberBitMapHeight() - HITBOX_RING_HEIGHT,
			FireRing2->GetLocationX() + HITBOX_RING_WIDTH, RING_LOCATION_Y + FireRing2->ReturnMemberBitMapHeight() };

		RECT LittleRingRectDown = { LittleFireRing->GetLocationX() - HITBOX_RING_WIDTH, RING_LOCATION_Y + LittleFireRing->ReturnMemberBitMapHeight() - HITBOX_RING_HEIGHT,
			LittleFireRing->GetLocationX() + HITBOX_RING_WIDTH, RING_LOCATION_Y + LittleFireRing->ReturnMemberBitMapHeight() };

		if (IntersectRect(&TmpRect, &CharacterRect, &Ring1RectDown) || IntersectRect(&TmpRect, &CharacterRect, &Ring2RectDown) || IntersectRect(&TmpRect, &CharacterRect, &LittleRingRectDown))
		{
                            			return true;	//�ε�ģ �Ϳ� ���� ���� ��ȯ�Ѵ�
		}
	}

	//{
	//	
	//	
	//	
	//	
	//	
	//	
	//	
	//	
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

	//	GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);	//�� ��Ʈ�� ������ ����
	//	int RingSizeY = BitMapImageSize.bmHeight;

	//	RECT Ring1RectUp = { m_Ring1XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y, m_Ring1XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y - RING_COLLISION_HEIGHT_PIEXL };
	//	RECT Ring1RectDown = { m_Ring1XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY - RING_COLLISION_HEIGHT_PIEXL,
	//		m_Ring1XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY };
	//	RECT Ring2RectUp = { m_Ring2XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y, m_Ring2XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y - RING_COLLISION_HEIGHT_PIEXL };
	//	RECT Ring2RectDown = { m_Ring2XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY - RING_COLLISION_HEIGHT_PIEXL,
	//		m_Ring2XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY };

	//	BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_LITTLERING_1);

	//	GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);	//�� ��Ʈ�� ������ ����
	//	RingSizeY = BitMapImageSize.bmHeight;

	//	RECT LittleRingRectUp = { m_LittleRingXLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y, m_LittleRingXLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y - RING_COLLISION_HEIGHT_PIEXL };
	//	RECT LittleRingRectDown = { m_LittleRingXLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY - RING_COLLISION_HEIGHT_PIEXL,
	//		m_LittleRingXLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY };

	//	if (IntersectRect(&TmpRect, &PlayerRect, &Ring1RectUp) || IntersectRect(&TmpRect, &PlayerRect, &Ring1RectDown) || IntersectRect(&TmpRect, &PlayerRect, &Ring2RectUp)
	//	|| IntersectRect(&TmpRect, &PlayerRect, &Ring2RectDown) || IntersectRect(&TmpRect, &PlayerRect, &LittleRingRectUp) || IntersectRect(&TmpRect, &PlayerRect, &LittleRingRectDown))
	//	{
	//		return true;	//�ε�ģ �Ϳ� ���� ���� ��ȯ�Ѵ�
	//	}
	//}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return false; //�ƹ��͵� �� �ε�ħ
}

HBITMAP DrawManager::CreateDIBSectionRe(HDC hdc, int width, int height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));
	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bm_info.bmiHeader.biBitCount = 24;  // �÷� ��(color bits) : 1, 4, 8, 16, 24, 31
	bm_info.bmiHeader.biWidth = width;  // �ʺ�.
	bm_info.bmiHeader.biHeight = height;// ����.
	bm_info.bmiHeader.biPlanes = 1;

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}


DrawManager::~DrawManager()
{
	DeleteDC(m_MemDCBack);
}