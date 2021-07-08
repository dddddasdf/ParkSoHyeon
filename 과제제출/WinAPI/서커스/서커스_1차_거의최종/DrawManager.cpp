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
	PointImage = ResourceMgr->ReturnPointBitMapClass();
	m_GameOverSelect = 0;

	//��Ʈ ����... - ������
	m_FontCustomize = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "����");

	//�� ������Ʈ ����...
	GoalObject = new Goal(hdc, LOCATION_GOAL_X);

	//ȭ�� Ŭ���� �迭(����0 �ʱ�ȭ
	
	for (int i = 1; i < MAP_WIDTH / FIRE_DISTANCE; i++)
	{
		Fire *fire = new Fire(m_MemDCBack, FIRE_DISTANCE * i);
		m_FireVector.push_back(fire);
	}
	Fire* LastFire = new Fire(m_MemDCBack, NULL);	//�� �տ� �ִ� ������ ȭ�� ����
	LastFire->SetLocationX(LOCATION_GOAL_X - LastFire->ReturnMemberBitMapWidth() - LOCATION_CHARACTER_VERTICAL);
	m_FireVector.push_back(LastFire);
}

void DrawManager::DeadInit()
{
	//X��ǥ�� ó�� ��ġ�� �ǵ��� �ָ� �ȴ�

	FireRing1->SetLocationX(LOCATION_RING1_START);
	FireRing2->SetLocationX(LOCATION_RING2_START);
	LittleFireRing->SetLocationX(LOCATION_LITTLERING_START);
	Cash1->SetLocationX(LOCATION_LITTLERING_START);
	Cash1->SwitchOnCash();	//���� ����ġ �ʱ�ȭ

	//ȭ�� ���� ����ġ �ʱ�ȭ
	for (int i = 0; i < ((LOCATION_GOAL_X - FIRE_DISTANCE) / FIRE_DISTANCE) - 1; i++)
	{
		(m_FireVector.at(i))->SwitchOnScore();
	}
}

void DrawManager::DrawImages(HDC hdc, const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation, const int& Life, const int& Score, const int& BonusScore)
{	
	//�� ȭ��

	HBITMAP BitMapBack = CreateDIBSectionRe(hdc, m_WindowWidth, m_WindowHeight);
	HBITMAP OldBitMapBack = (HBITMAP)SelectObject(m_MemDCBack, BitMapBack);
	
	bool Tmp = m_WindowWidth >= MAP_WIDTH - CharacterXLocation + LOCATION_CHARACTER_VERTICAL;	//���� ������ ������ ���̱� �����ߴ°�?�� ���� ����

	switch (Tmp)
	{
	case false:
	{
		//��� ���
		Map->Draw(m_MemDCBack, CharacterXLocation);

		//��� �׸��� ��Ʈ ��

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
			int Tmp = CharacterXLocation / FIRE_DISTANCE;	//���° ȭ�κ��� ����ؾ� �ϴ��� �˱� ���� �ӽ÷� ���� ����

			for (int i = 0; i <= 2; i++)
			{
				if ((m_FireVector.size()) > Tmp + i)
					(m_FireVector.at(Tmp + i))->Draw(m_MemDCBack, CharacterXLocation);	//������ ȭ�ΰ� �Ǿ ���� �� ������ �� ���� ��쿡 ���� ����ó��
				else
					break;
			}
			//�� ���� 3���� ����ϸ� �ȴ�
		}

		//��ֹ� �׸��� ��Ʈ1 ��
		
		//�� �׸�
		GoalObject->Draw(m_MemDCBack, CharacterXLocation);

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

		//��ֹ� �׸��� ��Ʈ2 ��

		
	}
		break;
	case true:
	{
		//��� ���
		Map->DrawFinal(m_MemDCBack, m_WindowWidth);

		//��� �׸��� ��Ʈ ��

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//��ֹ� �׸��� ��Ʈ1 (�� �� ���� ��, ȭ��)

		//�� �� ���� �׸�
		{
			FireRing1->DrawFinal(m_MemDCBack, m_WindowWidth);
			FireRing2->DrawFinal(m_MemDCBack, m_WindowWidth);
		}

		//���� �� �� ���� �׸�
		{
			LittleFireRing->DrawFinal(m_MemDCBack, m_WindowWidth);
		}

		//���ָӴ� �׸� - m_IsCashSwitchOn�� true�� ���� �׸��� �Լ��� �����Ѵ�
		{
			Cash1->DrawFinal(m_MemDCBack, m_WindowWidth);
		}

		//ȭ�� �׸�
		{
			(m_FireVector.at(m_FireVector.size() - 2))->DrawFinal(m_MemDCBack, m_WindowWidth);
			(m_FireVector.at(m_FireVector.size() - 1))->DrawFinal(m_MemDCBack, m_WindowWidth);

			//���� ������ �κп����� ȭ�ΰ� �� ���� ���� ���ۿ� �����Ƿ� ������ ���� �̿��� �ε����� ã�Ƴ��� �ȴ�
		}

		//��ֹ� �׸��� ��Ʈ1 ��

		//�� �׸�
		GoalObject->DrawFinal(m_MemDCBack, m_WindowWidth);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//ĳ���� �׸��� ��Ʈ

		int CharacterXTmp = m_WindowWidth - (MAP_WIDTH - CharacterXLocation);	//�� ��� ���� ĳ���� ȭ�� ǥ�� ��ġ �ӽ� ��ǥ
		CharacterObject->DrawCharacterFinal(m_MemDCBack, CharacterXTmp, CharacterYLocation, MotionNumber);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//��ֹ� �׸��� ��Ʈ2 (�� �� ������ ��)

		//�� �� ������ �׸�
		{
			FireRing1->DrawFinal(m_MemDCBack, m_WindowWidth);
			FireRing2->DrawFinal(m_MemDCBack, m_WindowWidth);
		}

		//���� �� �� ������ �׸�
		{
			LittleFireRing->DrawFinal(m_MemDCBack, m_WindowWidth);
		}

		//��ֹ� �׸��� ��Ʈ2 ��
	
	}
		break;
	}
	
	//��ֹ� ��� - �̾��� �� ������ �ؽ�Ʈ ��¿� �ӽ�
	HDC MemDCObstacle = CreateCompatibleDC(hdc);
	HBITMAP OlbBitMapObstacle;
	HBITMAP BitMapObstacle = NULL;

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

	BitBlt(hdc, 0, 0, m_WindowWidth, m_WindowHeight, m_MemDCBack, 0, 0, SRCCOPY);	//�� ȭ�鿡 ���
	SelectObject(m_MemDCBack, OldBitMapBack);


	DeleteDC(MemDCObstacle);
	DeleteObject(BitMapBack);
	/////////////////////////////////////////////////////////////////////////////////////////////////

}

void DrawManager::MoveRings(float MovingRingPixel, float MovingLittleRingPixel, int CharacterLocationX)
{
	bool Tmp = m_WindowWidth >= MAP_WIDTH - CharacterLocationX + LOCATION_CHARACTER_VERTICAL;	//���� ������ ������ ���̱� �����ߴ°�?�� ���� ����

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
	bool Tmp = m_WindowWidth >= MAP_WIDTH - CharacterXLocation + LOCATION_CHARACTER_VERTICAL;	//���� ������ ������ ���̱� �����ߴ°�?�� ���� ����

	switch (Tmp)
	{
	case false:
		CharacterRect = { CharacterXLocation + LOCATION_CHARACTER_VERTICAL, CharacterYLocation - CharacterObject->ReturnMemberBitMapHeight() + HITBOX_CHARACTER_HEIGHT_UP,
		CharacterXLocation + CharacterObject->ReturnMemberBitMapWidth() + (LONG)(LOCATION_CHARACTER_VERTICAL * 0.5f), CharacterYLocation - HITBOX_CHARACTER_HEIGHT_DOWN };	
		//ȭ�鿡 ���̴� ���� ��ġ ���� ������ CHARACTER_LOCATION_X�� �߰������ ��
		//������ �簢��
		break;
	case true:
		CharacterRect = { CharacterXLocation, CharacterYLocation - CharacterObject->ReturnMemberBitMapHeight() + HITBOX_CHARACTER_HEIGHT_UP,
		CharacterXLocation + CharacterObject->ReturnMemberBitMapWidth(), CharacterYLocation - HITBOX_CHARACTER_HEIGHT_DOWN };
		break;
	}

	int Score_Tmp = 0;	//���� ��ֹ� ���� ���� ������ ���� �ӽ�
	int User_Tmp = CharacterXLocation + LOCATION_CHARACTER_VERTICAL + CharacterObject->ReturnMemberBitMapWidth() * 0.5f;	//������ ���� ���� ĳ���Ͱ� ���� X��ǥ

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ȭ�ο� �ε��ƴ��� üũ��
	int Fire_Tmp = CharacterXLocation / FIRE_DISTANCE;	//���° ȭ�κ��� �浹 üũ �ؾ� �ϴ��� �ӽ÷� ���� ����
	//���� ������ �Ѿ�� ���� ���Ƿ�... üũ�ϴ� if ���� �ʿ�
	{
		if (Fire_Tmp < m_FireVector.size())
		{
			RECT FireRectLeft = { m_FireVector.at(Fire_Tmp)->GetLocationX() + (m_FireVector.at(Fire_Tmp)->ReturnMemberBitMapWidth() * 0.5f) - HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL,
			LOCATION_FIRE_Y - HITBOX_FIRE_UP,
			m_FireVector.at(Fire_Tmp)->GetLocationX() + (m_FireVector.at(Fire_Tmp)->ReturnMemberBitMapWidth() * 0.5f) + HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL,
			LOCATION_FIRE_Y };

			if (IntersectRect(&TmpRect, &CharacterRect, &FireRectLeft))
			{
				return CRASHED_OBJECT;	//�ε�ģ �Ϳ� ���� ���� ��ȯ�Ѵ�
			}
		}
		
		if (Fire_Tmp  + 1 < m_FireVector.size())
		{
			RECT FireRectRight = { m_FireVector.at(Fire_Tmp + 1)->GetLocationX() + (m_FireVector.at(Fire_Tmp + 1)->ReturnMemberBitMapWidth() * 0.5f) - HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL,
				LOCATION_FIRE_Y - HITBOX_FIRE_UP,
				m_FireVector.at(Fire_Tmp + 1)->GetLocationX() + (m_FireVector.at(Fire_Tmp + 1)->ReturnMemberBitMapWidth() * 0.5f) + HITBOX_FIRE_WIDTH - LOCATION_CHARACTER_VERTICAL, LOCATION_FIRE_Y };

			if (IntersectRect(&TmpRect, &CharacterRect, &FireRectRight))
			{
				return CRASHED_OBJECT;	//�ε�ģ �Ϳ� ���� ���� ��ȯ�Ѵ�
			}
		}

		//LOCATION_CHARACTER_VERTICAL�� ��ġ�� ���� ������
	}
	
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


	//���� ���� �κ�
	//��1
	if (User_Tmp >= FireRing1->GetLocationX() && User_Tmp <= FireRing1->GetLocationX() + MOVE_PIXEL && 
		CharacterYLocation <= LOCATION_RING_Y + FireRing1->ReturnMemberBitMapHeight() && true == FireRing1->ReturnScoreSwitch())
	{
 		Score_Tmp += SCORE_RING;
		FireRing1->SwitchOffScore();
	}
       	
	//��2
	if (User_Tmp >= FireRing2->GetLocationX() && User_Tmp <= FireRing2->GetLocationX() + MOVE_PIXEL &&
		CharacterYLocation <= LOCATION_RING_Y + FireRing2->ReturnMemberBitMapHeight() && true == FireRing2->ReturnScoreSwitch())
	{
		Score_Tmp += SCORE_RING;
		FireRing2->SwitchOffScore();
	}

	//���� ��
	if (User_Tmp >= LittleFireRing->GetLocationX() && User_Tmp <= LittleFireRing->GetLocationX() + MOVE_PIXEL &&
		CharacterYLocation <= LOCATION_RING_Y + LittleFireRing->ReturnMemberBitMapHeight() && true == LittleFireRing->ReturnScoreSwitch())
	{
		Score_Tmp += SCORE_RING;
		LittleFireRing->SwitchOffScore();
	}

	//ȭ��
	if (User_Tmp >= m_FireVector.at(Fire_Tmp)->GetLocationX() - LOCATION_CHARACTER_VERTICAL && User_Tmp <= m_FireVector.at(Fire_Tmp)->GetLocationX() + MOVE_PIXEL &&
		CharacterYLocation <= LOCATION_FIRE_Y + m_FireVector.at(Fire_Tmp)->ReturnMemberBitMapHeight() - LOCATION_CHARACTER_VERTICAL && true == m_FireVector.at(Fire_Tmp)->ReturnScoreSwitch())
	{
		Score_Tmp += SCORE_RING;
		m_FireVector.at(Fire_Tmp)->SwitchOffScore();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Score_Tmp; //�Ѿ ��ֹ� ���� ���� �������Ѿ� �� ���� ����
}

bool DrawManager::IsInGoal_In(const int& CharacterXLocation, const int& CharacterYLocation)
{
	int User_Tmp = CharacterXLocation + LOCATION_CHARACTER_VERTICAL + CharacterObject->ReturnMemberBitMapWidth() * 0.5f;	//������ ���� ���� ĳ���Ͱ� ���� X��ǥ
	
	if (User_Tmp >= GoalObject->GetLocationX() + (GoalObject->ReturnMemberBitMapWidth() * 0.5f) && 
		((User_Tmp >= GoalObject->GetLocationY() - JUMP_PIXEL * 0.5f) || User_Tmp <= GoalObject->GetLocationY() + JUMP_PIXEL * 0.5f))
	{
		
		return true;
	}

	return false;
}

void DrawManager::DrawWinImages(HDC hdc, const int& CharacterXLocation, const int& CharacterYLocation, const int& Life, const int& Score, const int& BonusScore, const int& MotionNumber)
{
	int CharacterXTmp = m_WindowWidth - (MAP_WIDTH - CharacterXLocation);	//�� ��� ���� ĳ���� ȭ�� ǥ�� ��ġ �ӽ� ��ǥ
	
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
		str = "�����̽��ٸ� ������ ���� ����";
		TextOut(m_MemDCBack, (m_WindowWidth * 0.5f) - (str.length() * 0.5f * 5), LOCATION_SCORE_Y + 20, str.c_str(), str.length());
	}

	BitBlt(hdc, 0, 0, m_WindowWidth, m_WindowHeight, m_MemDCBack, 0, 0, SRCCOPY);	//�� ȭ�鿡 ���
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
	std::string str = "���� ����";
	TextOut(m_MemDCBack, (m_WindowWidth * 0.5f), 250, str.c_str(), str.length());
	str = "�����̽��ٸ� ������ ���� ����";
	TextOut(m_MemDCBack, (m_WindowWidth * 0.5f), 350, str.c_str(), str.length());

	BitBlt(hdc, 0, 0, m_WindowWidth, m_WindowHeight, m_MemDCBack, 0, 0, SRCCOPY);	//�� ȭ�鿡 ���
	SelectObject(m_MemDCBack, OldBitMapBack);
	DeleteObject(BitMapBack);
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