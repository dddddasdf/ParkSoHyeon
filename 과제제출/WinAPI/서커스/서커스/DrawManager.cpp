#include "DrawManager.h"

#define TEST_LOCATION 500	//�׽�Ʈ�� �� �ӽ� ��ǥ

void DrawManager::Init(HWND hWnd)
{
	//������ ũ�� ���ؼ� ������ ��� ������ �־�α�
	RECT WindowRect;
	GetWindowRect(hWnd, &WindowRect);
	m_WindowWidth = WindowRect.right - WindowRect.left;
	m_WindowHeight = WindowRect.bottom - WindowRect.top;

	{
		//��� �� Ÿ��-���� ���� ����
		if (!m_BackgroundTileVector.empty())
			m_BackgroundTileVector.clear();

		m_BackgroundTileVector.push_back(BACKGROUND_ELEPHANT);
		for (int i = 1; i <= CROWD_PATTERN; i++)
		{
			m_BackgroundTileVector.push_back(BACKGROUND_CROWD_FIRST);
		}
	}
	
	{
		//�� �̹��� ������ �̸� ���س���
		HBITMAP HBitmapTmp;
		BITMAP BitmapTmp;

		HBitmapTmp = ResourceMgr->ReturnBackgroundImage(BACKGROUND_FLOOR);
		GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);

		m_FloorImageSizeWidth = BitmapTmp.bmWidth;
		m_FloorImageSizeHeight = BitmapTmp.bmHeight;	//�ٴ� ������

		HBitmapTmp = ResourceMgr->ReturnBackgroundImage(BACKGROUND_CROWD_FIRST);
		GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);

		m_CrowdImageSizeWidth = BitmapTmp.bmWidth;
		m_CrowdImageSizeHeight = BitmapTmp.bmHeight;	//���� ������

		HBitmapTmp = ResourceMgr->ReturnObstacleImage(OBSTACLE_CASH);
		GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);

		m_CashSizeWidth = BitmapTmp.bmWidth;
		m_CashSizeHeight = BitmapTmp.bmHeight;	//���ָӴ� ������

		HBitmapTmp = ResourceMgr->ReturnObstacleImage(OBSTACLE_FIRE_1);
		GetObject(HBitmapTmp, sizeof(BITMAP), &BitmapTmp);

		m_FireSizeWidth = BitmapTmp.bmWidth;
		m_FireSizeHeight = BitmapTmp.bmHeight;	//ȭ�� ������
	}
	
	//Y��ǥ ���� �κ�
	m_FloorYStart = HORIZON_HEIGHT - m_FloorImageSizeHeight;	//�ٴ� Ÿ�� ���� Y��ǥ
	m_CrowdYStart = HORIZON_HEIGHT - m_FloorImageSizeHeight - m_CrowdImageSizeHeight;	//���� Ÿ�� ���� Y��ǥ

	{
		//ȭ�� X��ǥ ���� ����
		if (!m_ObstacleFireXLocation.empty())
			m_ObstacleFireXLocation.clear();	//�̰� ���� �� ���� ����

		for (int i = FIRE_DISTANCE; i <= END_OF_MAP; i += FIRE_DISTANCE)
			m_ObstacleFireXLocation.push_back(i);	//ȭ�δ� 500�ȼ� �������� ��ġ�Ǿ� �ִ�

		m_FireAnimation = OBSTACLE_FIRE_1;	//����� ȭ�� �ִϸ��̼��� ���� ��������� �ʱ�ȭ
	}

	{
		//�� X��ǥ �ʱ� ��ġ ����
		m_Ring1XLocation = 500;
		m_Ring2XLocation = 1000;
		m_LittleRingXLocation = 2500;

		m_RingAnimation = OBSTACLE_RING_FIRST_1;	//����� �� �ִϸ��̼��� ���� ��������� �ʱ�ȭ
	}

	m_IsCashSwitchOn = true;	//���ָӴ� ����ġ ��
}

void DrawManager::DeadInit()
{
	//X��ǥ�� ó�� ��ġ�� �ǵ��� �ָ� �ȴ�

	//�� X��ǥ �ʱ� ��ġ ����
	m_Ring1XLocation = 500;
	m_Ring2XLocation = 1000;
	m_LittleRingXLocation = 2000;

	m_IsCashSwitchOn = true;	//���ָӴ� ����ġ ��
}

void DrawManager::DrawImages(HDC hdc, const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation)
{	
	//�� ȭ��
	HDC MemDCBack = CreateCompatibleDC(hdc);
	HBITMAP BitMapBack = CreateDIBSectionRe(hdc, m_WindowWidth, m_WindowHeight);
	HBITMAP OldBitMapBack = (HBITMAP)SelectObject(MemDCBack, BitMapBack);

	BITMAP BitMapImageSize;	//�̹��� ���� ũ�⸦ ���ϱ� ���� ��Ʈ��

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��� ���
	HDC MemDCBackground = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapBackground;
	HBITMAP BitMapBackground = NULL;


	//��� �׸��� ��Ʈ - �ٴ�
	BitMapBackground = ResourceMgr->ReturnBackgroundImage(BACKGROUND_FLOOR);
	OlbBitMapBackground = (HBITMAP)SelectObject(MemDCBackground, BitMapBackground);

	for (int i = 0; i < (m_WindowWidth / m_FloorImageSizeWidth + 1); i++)
	{
		TransparentBlt(MemDCBack, m_FloorImageSizeWidth * i, m_FloorYStart, m_FloorImageSizeWidth, m_FloorImageSizeHeight, 
			MemDCBackground, 0, 0, m_FloorImageSizeWidth, m_FloorImageSizeHeight, RGB(255, 0, 255));
	}


	//��� �׸��� ��Ʈ - ����
	int StartBlock = CharacterXLocation / m_CrowdImageSizeWidth;	//�÷��̾� ��ġ�� ���� ������ ���� ���ؾ� ��
	int CutWidth = CharacterXLocation - (m_CrowdImageSizeWidth * StartBlock);	//�÷��̾��� �� X ��ǥ�� ���� �߸��� ĭ�� ���� ���
	for (int i = StartBlock, j = 0; i < ((m_WindowWidth + m_CrowdImageSizeWidth) / m_CrowdImageSizeWidth + (StartBlock +1)); i++, j++)
	{
		BitMapBackground = ResourceMgr->ReturnBackgroundImage((m_BackgroundTileVector.at(i % CROWD_PATTERN)));
		OlbBitMapBackground = (HBITMAP)SelectObject(MemDCBackground, BitMapBackground);
		TransparentBlt(MemDCBack, (0 - CutWidth) + m_CrowdImageSizeWidth * j, m_CrowdYStart, m_CrowdImageSizeWidth, m_CrowdImageSizeHeight,
			MemDCBackground, 0, 0, m_CrowdImageSizeWidth, m_CrowdImageSizeHeight, RGB(255, 0, 255));
	}
	/*
	CutWidth�� �켱 ù��° Ÿ���� �߸��� ���̸� ���Ѵ�
	�׸��� ������ǥ�� x = 0���� �߸��� ���̸�ŭ ������ �ּ� �����ϰ� �Ѵ�
	������ Ÿ�ϵ��� Ÿ���� ������ ����(j)�� Ÿ���� ���̸� ���ؼ� �׷����� x��ǥ�� ���Ѵ�
	*/

	SelectObject(MemDCBackground, OlbBitMapBackground);

	//��� �׸��� ��Ʈ ��

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��ֹ� ���
	HDC MemDCObstacle = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapObstacle;
	HBITMAP BitMapObstacle = NULL;

	//��ֹ� �׸��� ��Ʈ1 (�� �� ���� ��, ȭ��)

	//�� �� ���� �׸�
	{
		switch (m_RingAnimation)
		{
		case OBSTACLE_RING_FIRST_1:
			BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_RING_FIRST_1);
			break;
		case OBSTACLE_RING_SECOND_1:
			BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_RING_SECOND_1);
			break;
		}
		//������ �� �׸� �� �ִϸ��̼� ���� �������ָ� ��

		GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);	//�� ��Ʈ�� ������ ����
		int RingSizeX = BitMapImageSize.bmWidth;
		int RingSizeY = BitMapImageSize.bmHeight;

		OlbBitMapObstacle = (HBITMAP)SelectObject(MemDCObstacle, BitMapObstacle);
		TransparentBlt(MemDCBack, m_Ring1XLocation - RingSizeX, RING_LOCATION_Y, RingSizeX, RingSizeY, MemDCObstacle, 0, 0, RingSizeX, RingSizeY, RGB(255, 0, 255));

		OlbBitMapObstacle = (HBITMAP)SelectObject(MemDCObstacle, BitMapObstacle);
		TransparentBlt(MemDCBack, m_Ring2XLocation - RingSizeX, RING_LOCATION_Y, RingSizeX, RingSizeY, MemDCObstacle, 0, 0, RingSizeX, RingSizeY, RGB(255, 0, 255));
	}

	//���� �� �� ���� �׸�
	{
		BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_LITTLERING_1);

		GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);	//�� ��Ʈ�� ������ ����
		int RingSizeX = BitMapImageSize.bmWidth;
		int RingSizeY = BitMapImageSize.bmHeight;

		OlbBitMapObstacle = (HBITMAP)SelectObject(MemDCObstacle, BitMapObstacle);
		TransparentBlt(MemDCBack, m_LittleRingXLocation - RingSizeX, RING_LOCATION_Y, RingSizeX, RingSizeY, MemDCObstacle, 0, 0, RingSizeX, RingSizeY, RGB(255, 0, 255));
	}

	//���ָӴ� �׸� - m_IsCashSwitchOn�� true�� ���� �׸��� �Լ��� �����Ѵ�
	{
		if (true == m_IsCashSwitchOn)
		{
			BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_CASH);

			GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);	//�� ��Ʈ�� ������ ����

			OlbBitMapObstacle = (HBITMAP)SelectObject(MemDCObstacle, BitMapObstacle);
			TransparentBlt(MemDCBack, m_LittleRingXLocation - (m_CashSizeWidth * 0.5f), RING_LOCATION_Y + 25, m_CashSizeWidth, m_CashSizeHeight, MemDCObstacle, 0, 0, m_CashSizeWidth, m_CashSizeHeight, RGB(255, 0, 255));
			//���ָӴϴ� ���� �� X��ǥ�� �����Ѵ�
		}
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

			TransparentBlt(MemDCBack, i, HORIZON_FIRE - m_FireSizeWidth, m_FireSizeWidth, m_FireSizeHeight, MemDCObstacle, 0, 0, m_FireSizeWidth, m_FireSizeHeight, RGB(255, 0, 255));
		}
	}

	//��ֹ� �׸��� ��Ʈ1 ��

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ĳ���� �׸��� ��Ʈ
	
	//ĳ���� ���
	HDC MemDCCharacter = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapCharacter;
	HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);

	{
		//�׸��� ����
		GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapImageSize);
		int CharacterSizeX = BitMapImageSize.bmWidth;
		int CharacterSizeY = BitMapImageSize.bmHeight;

		OlbBitMapCharacter = (HBITMAP)SelectObject(MemDCCharacter, BitMapCharacter);
		TransparentBlt(MemDCBack, CHARACTER_LOCATION_X, CharacterYLocation - CharacterSizeY, CharacterSizeX, CharacterSizeY, MemDCCharacter, 0, 0, CharacterSizeX, CharacterSizeY, RGB(255, 0, 255));
		SelectObject(MemDCCharacter, OlbBitMapCharacter);		
	}
	
	//ĳ���� �׸��� ��Ʈ ��
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��ֹ� �׸��� ��Ʈ2 (�� �� ������ ��)
	
	//�� �� ������ �׸�
	{
		//�׸��� ���� �κ�
		switch (m_RingAnimation)
		{
		case OBSTACLE_RING_FIRST_1:
			BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_RING_FIRST_2);
			m_RingAnimation = OBSTACLE_RING_SECOND_1;	//��Ʈ���� �޾ƿ� ���� �ִϸ��̼� ���� ������ �̸� ���� �ɷ� ��ü�ؼ� ���� ������ ��� �� �ٷιٷ� ����� ������ �ǵ��� �Ѵ�
			break;
		case OBSTACLE_RING_SECOND_1:
			BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_RING_SECOND_2);
			m_RingAnimation = OBSTACLE_RING_FIRST_1;
			break;
		}

		GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);	//�� ��Ʈ�� ������ ����
		int RingSizeX = BitMapImageSize.bmWidth;
		int RingSizeY = BitMapImageSize.bmHeight;

		OlbBitMapObstacle = (HBITMAP)SelectObject(MemDCObstacle, BitMapObstacle);
		TransparentBlt(MemDCBack, m_Ring1XLocation, RING_LOCATION_Y, RingSizeX, RingSizeY, MemDCObstacle, 0, 0, RingSizeX, RingSizeY, RGB(255, 0, 255));

		OlbBitMapObstacle = (HBITMAP)SelectObject(MemDCObstacle, BitMapObstacle);
		TransparentBlt(MemDCBack, m_Ring2XLocation, RING_LOCATION_Y, RingSizeX, RingSizeY, MemDCObstacle, 0, 0, RingSizeX, RingSizeY, RGB(255, 0, 255));
	}

	//���� �� �� ������ �׸�
	{
		BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_LITTLERING_2);

		GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);	//�� ��Ʈ�� ������ ����
		int RingSizeX = BitMapImageSize.bmWidth;
		int RingSizeY = BitMapImageSize.bmHeight;

		OlbBitMapObstacle = (HBITMAP)SelectObject(MemDCObstacle, BitMapObstacle);
		TransparentBlt(MemDCBack, m_LittleRingXLocation, RING_LOCATION_Y, RingSizeX, RingSizeY, MemDCObstacle, 0, 0, RingSizeX, RingSizeY, RGB(255, 0, 255));
	}


	SelectObject(MemDCObstacle, OlbBitMapObstacle);

	//��ֹ� �׸��� ��Ʈ2 ��

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	BitBlt(hdc, 0, 0, m_WindowWidth, m_WindowHeight, MemDCBack, 0, 0, SRCCOPY);	//�� ȭ�鿡 ���
	SelectObject(MemDCBack, OldBitMapBack);


	DeleteDC(MemDCCharacter);
	DeleteDC(MemDCBackground);
	DeleteDC(MemDCBack);
	DeleteDC(MemDCObstacle);
	DeleteObject(BitMapBack);
	/////////////////////////////////////////////////////////////////////////////////////////////////

}

void DrawManager::MoveRings(float MovingRingPixel, float MovingLittleRingPixel)
{
	//�� �� X ��ǥ �����ϴ� �κ�
	m_Ring1XLocation -= MovingRingPixel;
	m_Ring2XLocation -= MovingRingPixel;

	if (m_Ring1XLocation < CHARACTER_LOCATION_X - 50)
		m_Ring1XLocation = 1200 + (CHARACTER_LOCATION_X - 50);

	if (m_Ring2XLocation < CHARACTER_LOCATION_X - 50)
		m_Ring2XLocation = 1200 + (CHARACTER_LOCATION_X - 50);

	//���� �� �� X ��ǥ �����ϴ� �κ�
	m_LittleRingXLocation -= MovingLittleRingPixel;

	if (m_LittleRingXLocation < CHARACTER_LOCATION_X - 50)
	{
		m_LittleRingXLocation = 3500 + (CHARACTER_LOCATION_X - 50);
		m_IsCashSwitchOn = true;	//����� ���ָӴ� ����ġ�� ���� �Ѽ� ����������...
	}
}

bool DrawManager::IsCashCollision(const int& MotionNumber, const int& CharacterYLocation)
{
	if (true == m_IsCashSwitchOn)
	{
		//���ָӴϰ� �� �Ǿ����� ���� üũ�ϸ� �ȴ�... �Ծ ���� ���ȿ��� ���� �������� ���ǹ�
		HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
		BITMAP BitMapImageSize;

		GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapImageSize);
		int CharacterSizeX = BitMapImageSize.bmWidth;
		int CharacterSizeY = BitMapImageSize.bmHeight;
		//������� ĳ���� ��Ʈ�� ������ ���ϴ� �κ�

		RECT TmpRect;
		RECT PlayerRect = { CHARACTER_LOCATION_X, CharacterYLocation - CharacterSizeY, CHARACTER_LOCATION_X + CharacterSizeX, CharacterYLocation };
		RECT CashRect = { m_LittleRingXLocation - (m_CashSizeWidth * 0.5f), RING_LOCATION_Y + 25, m_LittleRingXLocation + (m_CashSizeWidth * 0.5f), (RING_LOCATION_Y + 25) + m_CashSizeHeight };

		if (IntersectRect(&TmpRect, &PlayerRect, &CashRect))
		{
			m_IsCashSwitchOn = false;
			return true;	//�ε�ģ �Ϳ� ���� ���� ��ȯ�Ѵ�
		}
	}

	return false;	//�ƹ� �ϵ� �������� false ��ȯ
}

bool DrawManager::IsObstacleCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation)
{
	HBITMAP BitMapCharacter = ResourceMgr->ReturnCharacterImage(MotionNumber);
	BITMAP BitMapImageSize;

	GetObject(BitMapCharacter, sizeof(BITMAP), &BitMapImageSize);
	int CharacterSizeX = BitMapImageSize.bmWidth;
	int CharacterSizeY = BitMapImageSize.bmHeight;
	//������� ĳ���� ��Ʈ�� ������ ���ϴ� �κ�

	RECT TmpRect;
	RECT PlayerRect = { CharacterXLocation, CharacterYLocation - CharacterSizeY, CharacterXLocation + CharacterSizeX, CharacterYLocation };	//���� �簢��(�� ����)

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ȭ�ο� �ε��ƴ��� üũ��
	{
		int FireXLocation = FIRE_DISTANCE - (CharacterXLocation % FIRE_DISTANCE) - 40 + CharacterXLocation - m_FireSizeWidth + 25;

		RECT FireRectLeft = { FireXLocation, HORIZON_FIRE - m_FireSizeHeight + 10, FireXLocation + m_FireSizeWidth - 15, HORIZON_FIRE };
		RECT FireRectRight = { FireXLocation + FIRE_DISTANCE, HORIZON_FIRE - m_FireSizeHeight + 10, (FireXLocation + FIRE_DISTANCE) + m_FireSizeWidth - 15, HORIZON_FIRE };
		//���װ� �ƴ� �̻� ���� ���� �ι�° ȭ�ο� �ε�ĥ ���� �����Ƿ� ���� ������ ȭ�� �ϳ� �������� ȭ�� �ϳ��� üũ�ϸ� ������ ��
		//���� �ʹ� ������ ��� ���ݾ� ���°��� �������ִ� ����...

		if (IntersectRect(&TmpRect, &PlayerRect, &FireRectLeft))
		{
			return true;	//�ε�ģ �Ϳ� ���� ���� ��ȯ�Ѵ�
		}
		if (IntersectRect(&TmpRect, &PlayerRect, &FireRectRight))
		{
			return true;	//�ε�ģ �Ϳ� ���� ���� ��ȯ�Ѵ�
		}
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//���� �ε��ƴ��� üũ��
	//���� ���κ� �Ʒ��κ����� �ɰ��� �� �Ѱ� �ε��ƴ��� üũ�Ѵ�

	{
		BITMAP BitMapSize;
		HBITMAP BitMapObstacle = NULL;
		switch (m_RingAnimation)
		{
		case OBSTACLE_RING_FIRST_1:
			BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_RING_FIRST_1);
			break;
		case OBSTACLE_RING_SECOND_1:
			BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_RING_SECOND_1);
			break;
		}

		GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);	//�� ��Ʈ�� ������ ����
		int RingSizeY = BitMapImageSize.bmHeight;

		RECT Ring1RectUp = { m_Ring1XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y, m_Ring1XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y - RING_COLLISION_HEIGHT_PIEXL };
		RECT Ring1RectDown = { m_Ring1XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY - RING_COLLISION_HEIGHT_PIEXL,
			m_Ring1XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY };
		RECT Ring2RectUp = { m_Ring2XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y, m_Ring2XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y - RING_COLLISION_HEIGHT_PIEXL };
		RECT Ring2RectDown = { m_Ring2XLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY - RING_COLLISION_HEIGHT_PIEXL,
			m_Ring2XLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY };

		BitMapObstacle = ResourceMgr->ReturnObstacleImage(OBSTACLE_LITTLERING_1);

		GetObject(BitMapObstacle, sizeof(BITMAP), &BitMapImageSize);	//�� ��Ʈ�� ������ ����
		RingSizeY = BitMapImageSize.bmHeight;

		RECT LittleRingRectUp = { m_LittleRingXLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y, m_LittleRingXLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y - RING_COLLISION_HEIGHT_PIEXL };
		RECT LittleRingRectDown = { m_LittleRingXLocation - RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY - RING_COLLISION_HEIGHT_PIEXL,
			m_LittleRingXLocation + RING_COLLISION_WIDTH_PIEXL, RING_LOCATION_Y + RingSizeY };

		if (IntersectRect(&TmpRect, &PlayerRect, &Ring1RectUp) || IntersectRect(&TmpRect, &PlayerRect, &Ring1RectDown) || IntersectRect(&TmpRect, &PlayerRect, &Ring2RectUp)
		|| IntersectRect(&TmpRect, &PlayerRect, &Ring2RectDown) || IntersectRect(&TmpRect, &PlayerRect, &LittleRingRectUp) || IntersectRect(&TmpRect, &PlayerRect, &LittleRingRectDown))
		{
			return true;	//�ε�ģ �Ϳ� ���� ���� ��ȯ�Ѵ�
		}
	}

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
