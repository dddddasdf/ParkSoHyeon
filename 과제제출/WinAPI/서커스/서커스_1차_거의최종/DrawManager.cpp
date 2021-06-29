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

	FireRing1 = new Ring1(hdc, LOCATION_RING1_START);
	FireRing2 = new Ring1(hdc, LOCATION_RING2_START);
	LittleFireRing = new LittleRing(hdc, LOCATION_LITTLERING_START);
	Cash1 = new Cash(hdc, LOCATION_LITTLERING_START);
	Map = new MapTile(hdc, NULL);
	CharacterObject = new Character(hdc, NULL);


	//������ ��Ʈ�� �޾Ƶα�... ������Ʈ�� ���� �� �ʿ䰡 ���ٰ� �Ǵ��ؼ� ��� ǥ�ô� ��Ʈ�����θ� ����
	LifeImage = ResourceMgr->ReturnInterfaceBitMapClass(2);

	//��Ʈ ����... - ������
	m_FontCustomize = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "����");

	//ȭ�� Ŭ���� �迭 �ʱ�ȭ
	int Tmp = (LOCATION_GOAL_X - FIRE_DISTANCE) / FIRE_DISTANCE;
	FireObjects = new Fire[Tmp];	//���ͷ� ����
	
	for (int i = 1; i < (LOCATION_GOAL_X - FIRE_DISTANCE) / FIRE_DISTANCE; i++)
	{
		//
	}


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

	FireRing1->SetLocationX(LOCATION_RING1_START);
	FireRing2->SetLocationX(LOCATION_RING2_START);
	LittleFireRing->SetLocationX(LOCATION_LITTLERING_START);
	Cash1->SetLocationX(LOCATION_LITTLERING_START);
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

			TransparentBlt(m_MemDCBack, i, LOCATION_FIRE_Y - m_FireSizeWidth, m_FireSizeWidth, m_FireSizeHeight, MemDCObstacle, 0, 0, m_FireSizeWidth, m_FireSizeHeight, RGB(255, 0, 255));
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
		TransparentBlt(m_MemDCBack, LOCATION_LIFE_X - LifeImage.ReturnBitMapWidth() * i, LOCATION_LIFE_Y, LifeImage.ReturnBitMapWidth(), LifeImage.ReturnBitMapHeight(), 
			MemDCObstacle, 0, 0, LifeImage.ReturnBitMapWidth(), LifeImage.ReturnBitMapHeight(), RGB(255, 0, 255));
	}

	//auto font = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "�ü�");
	//SelectObject(m_MemDCBack, font);
	SelectObject(m_MemDCBack, m_FontCustomize);
	SetTextColor(m_MemDCBack, RGB(255, 255,255));
	SetBkMode(m_MemDCBack, TRANSPARENT);
	std::string str = std::to_string(Score);
	TextOut(m_MemDCBack, LOCATION_SCORE_X, LOCATION_SCORE_Y, str.c_str(), str.length());
	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef Debug_Coll
	Rectangle(m_MemDCBack, Ring1RectDown.left, Ring1RectDown.top, Ring1RectDown.right, Ring1RectDown.bottom);
	Rectangle(m_MemDCBack, Ring2RectDown.left, Ring2RectDown.top, Ring2RectDown.right, Ring2RectDown.bottom);
	Rectangle(m_MemDCBack, LittleRingRectDown.left, LittleRingRectDown.top, LittleRingRectDown.right, LittleRingRectDown.bottom);
	Rectangle(m_MemDCBack, CharacterRect.left, CharacterRect.top, CharacterRect.right, CharacterRect.bottom);
#endif // Debug_Coll

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
		RECT CharacterRectCash = { (CharacterXLocation + LOCATION_CHARACTER_VERTICAL) + (LONG)(CharacterObject->ReturnMemberBitMapWidth() * 0.5f) - HITBOX_CHARACTER_WIDTH, 
			CharacterYLocation - CharacterObject->ReturnMemberBitMapHeight(),
			(CharacterXLocation + LOCATION_CHARACTER_VERTICAL) + (LONG)(CharacterObject->ReturnMemberBitMapWidth() * 0.5f) + HITBOX_CHARACTER_WIDTH, CharacterYLocation - HITBOX_CHARACTER_HEIGHT_DOWN };
		//ȭ�鿡 ���̴� ���� ��ġ ���� ������ CHARACTER_LOCATION_X�� �߰������ ��
		//������ �簢��
		
		RECT CashRect = { Cash1->GetLocationX() - (Cash1->ReturnMemberBitMapWidth() * 0.5f), Cash1->GetLocationY(),
			Cash1->GetLocationX() + (Cash1->ReturnMemberBitMapWidth() * 0.5f), Cash1->GetLocationY() + Cash1->ReturnMemberBitMapHeight() };

		if (IntersectRect(&TmpRect, &CharacterRectCash, &CashRect))
		{
			Cash1->SwitchOffCash();	//�ε������� ���ָӴ� ����ġ ����
			return true;
		}
	}
	return false;	//�ƹ� �ϵ� �������� false ��ȯ
}

int DrawManager::IsObsjectCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation)
{
	RECT TmpRect;
	CharacterRect = { CharacterXLocation + LOCATION_CHARACTER_VERTICAL, CharacterYLocation - CharacterObject->ReturnMemberBitMapHeight() + HITBOX_CHARACTER_HEIGHT_UP,
		CharacterXLocation + CharacterObject->ReturnMemberBitMapWidth() + (LONG)(LOCATION_CHARACTER_VERTICAL * 0.5f), CharacterYLocation - HITBOX_CHARACTER_HEIGHT_DOWN };	//ȭ�鿡 ���̴� ���� ��ġ ���� ������ CHARACTER_LOCATION_X�� �߰������ ��
	//������ �簢��

	int Score_Tmp = 0;	//���� ��ֹ� ���� ���� ������ ���� �ӽ�
	int User_Tmp = CharacterXLocation + LOCATION_CHARACTER_VERTICAL + CharacterObject->ReturnMemberBitMapWidth() * 0.5f;

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
		Ring1RectDown = { FireRing1->GetLocationX() - HITBOX_RING_WIDTH, LOCATION_RING_Y + FireRing1->ReturnMemberBitMapHeight() - HITBOX_RING_HEIGHT,
		FireRing1->GetLocationX() + HITBOX_RING_WIDTH, LOCATION_RING_Y + FireRing1->ReturnMemberBitMapHeight() };
		Ring2RectDown = { FireRing2->GetLocationX() - HITBOX_RING_WIDTH, LOCATION_RING_Y + FireRing2->ReturnMemberBitMapHeight() - HITBOX_RING_HEIGHT,
		FireRing2->GetLocationX() + HITBOX_RING_WIDTH, LOCATION_RING_Y + FireRing2->ReturnMemberBitMapHeight() };
		LittleRingRectDown = { LittleFireRing->GetLocationX() - HITBOX_RING_WIDTH, LOCATION_RING_Y + LittleFireRing->ReturnMemberBitMapHeight() - HITBOX_RING_HEIGHT,
			LittleFireRing->GetLocationX() + HITBOX_RING_WIDTH, LOCATION_RING_Y + LittleFireRing->ReturnMemberBitMapHeight() };

		if (IntersectRect(&TmpRect, &CharacterRect, &Ring1RectDown) || IntersectRect(&TmpRect, &CharacterRect, &Ring2RectDown) || IntersectRect(&TmpRect, &CharacterRect, &LittleRingRectDown))
		{
			return CRASHED_OBJECT;	//�ε�ģ �Ϳ� ���� ���� ��ȯ�Ѵ�
		}
	}

	//{
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

	//���� ���� �κ�
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

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Score_Tmp; //�Ѿ ��ֹ� ���� ���� �������Ѿ� �� ���� ����
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