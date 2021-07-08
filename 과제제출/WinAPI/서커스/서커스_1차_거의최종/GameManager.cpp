#include "GameManager.h"

void GameManager::WholeInit(HWND hWnd, HDC hdc)
{
	ResourceMgr->InitImages();
	DrawMgr->Init(hWnd, hdc);
	m_PlayerData = new Player;
	m_IsMoving = false;
	m_IsJumping = false;
	m_IsHighest = false;
	m_MovingDirection = NULL;
	m_IsDeadTrigger = false;
	m_BonusScore = BONUS_SCORE;
	m_NowState = STATE_NONE;
}

void GameManager::PartialInit()
{
	DrawMgr->DeadInit();
	m_PlayerData->DeadInit();
	
	m_IsMoving = false;
	m_IsJumping = false;
	m_IsHighest = false;
	m_MovingDirection = NULL;
	m_IsDeadTrigger = false;
	m_BonusScore = BONUS_SCORE;
	m_NowState = STATE_NONE;
}

void GameManager::MovingCharacter(const int& Key)
{
	switch (Key)
	{
	case VK_LEFT:
	case VK_RIGHT:
		m_PlayerData->ChangeMotion(MOTION_RUNNING);
		m_PlayerData->ChangeXLocation(Key);
		m_IsMoving = true;
		break;
	}
}

void GameManager::JumpingCharacter()
{
	m_PlayerData->ChangeMotion(MOTION_JUMPING);

	m_IsJumping = true;
}

void GameManager::ChangeCharacterYLocation()
{
	/*
	m_IsHighest�� ���� ���� �����Ѵ�. 
	false�� �� ���� ���������� �ø��� �ְ� ���� �����ϸ� m_IsHighest�� true�� ��ü�� ���� ���� ���������� ������
	���� ��ǥ�� �����ϸ� m_IsHighest�� false�� ������ m_IsJumping ���� false�� ���� ���� ���������� ĳ������ ����� ���ĵ����� ��ü�Ѵ�
	*/
	
	switch (m_IsHighest)
	{
	case false:
	{
		m_PlayerData->ChangeYLocation(true);
		if (JUMP_HEIGHT >= m_PlayerData->ReturnCharacterYLocation())
		{
			m_IsHighest = true;
		}
	}
		break;
	case true:
	{
		m_PlayerData->ChangeYLocation(false);
		if (LOCATION_CHARACTER_HORIZON <= m_PlayerData->ReturnCharacterYLocation())
		{
			m_IsHighest = false;
			m_IsJumping = false;
			StandingCharacter();
		}
	}
		break;
	}
}

void GameManager::StandingCharacter()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		switch (m_PlayerData->ReturnMotion())
		{
		case MOTION_JUMPING:
			m_PlayerData->ChangeMotion(MOTION_RUNNING);
			break;
		case MOTION_RUNNING:
			m_PlayerData->ChangeMotion(MOTION_JUMPING);
			break;
		}
		m_MovingDirection = VK_RIGHT;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		switch (m_PlayerData->ReturnMotion())
		{
		case MOTION_STAND:
			m_PlayerData->ChangeMotion(MOTION_RUNNING);
			break;
		case MOTION_RUNNING:
			m_PlayerData->ChangeMotion(MOTION_STAND);
			break;
		}
		m_MovingDirection = VK_LEFT;
	}
	else
	{
		m_PlayerData->ChangeMotion(MOTION_STAND);
		m_MovingDirection = NULL;
	}
		

	/*
	���� ���ϱ� ����� �޸��� �߿��� ĳ���� ��������Ʈ 2, 3�� �����ư��鼭 ��������
	�ϴ� ������ ���ؼ� �̷��� �Ͽ���... ����� �ٲٴ� �Լ��� �� �Լ��� ȣ��Ǵ� ���� Ű�Է��� ���������� �̷������ �ִٸ� �ٸ� �޸��� �������
	���ٸ� ���ĵ�����
	*/

	m_IsMoving = false;
}

void GameManager::CalculateRings(float elapsed)
{
	bool Tmp = DrawMgr->IsFinal(m_PlayerData->ReturnCharacterXLocation());	//�� ���κ��� ��ũ������ �����Ƿ� �����̳� ������ �̷������ �� �ȴ� �׷��� ���� �� ���κ����� Ȯ���ϴ� �ӽ� ����
	
	auto addSpeed = MOVE_PIXEL * 5;
	if (m_MovingDirection == VK_RIGHT && false == Tmp)
	{
		//MOVE_PIXEL * 40;
		DrawMgr->MoveRings((RING_MOVE_PIXEL + addSpeed) * elapsed, (LITTLERING_MOVE_PIXEL + addSpeed) * elapsed, m_PlayerData->ReturnCharacterXLocation());
	}
	else if (m_MovingDirection == VK_LEFT && m_PlayerData->ReturnCharacterXLocation() > 0 && false == Tmp)
	{
		DrawMgr->MoveRings((RING_MOVE_PIXEL - addSpeed) * elapsed, (LITTLERING_MOVE_PIXEL - addSpeed) * elapsed, m_PlayerData->ReturnCharacterXLocation());
	}
	else
		DrawMgr->MoveRings(RING_MOVE_PIXEL * elapsed, LITTLERING_MOVE_PIXEL * elapsed, m_PlayerData->ReturnCharacterXLocation());


	/*
	ó������ �� �Լ����� Ű�Է��� �������� ������ �� ��� ���� ���� ����Ű�� �ٲ������ ���� �ӵ��� �޶����� ������ �߻�
	�׷� ��� �����̴� �Լ����� ��� ������ ��� �������� �����̰� �ִٴ� ���� �����Ͽ� �� ������ �̿��Ͽ� ���� �������� ��ü�ϵ��� ��

	�����ϱ� �ߴµ� �� �ڽŵ� ������ �𸣰ڴ� ������ ����
	*/
}

void GameManager::CollisionCheck()
{
	if (DrawMgr->IsCashCollision(m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation()))
		m_PlayerData->PlusScore(SCORE_CASH);
	
	int Tmp = DrawMgr->IsObsjectCollision(m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation());

	if (CRASHED_OBJECT == Tmp)
	{
		m_PlayerData->ChangeMotion(MOTION_DEAD);
		m_IsDeadTrigger = true;
		m_NowState = STATE_DEAD;
		m_PlayerData->MinusLife();
	}
	else
		m_PlayerData->PlusScore(Tmp);
}

void GameManager::GoalInCheck()
{
	if (DrawMgr->IsInGoal_In(m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation()))
	{
		m_PlayerData->SetYLocation(353);
		GameMgr->ChangeWinningMotion();
		m_NowState = STATE_WIN;
	}
}

void GameManager::Winning(HDC *hdc)
{
	DrawMgr->DrawWinImages(*hdc, m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation(),
		m_PlayerData->ReturnLife(), m_PlayerData->ReturnScore(), m_BonusScore, m_PlayerData->ReturnMotion());
}

void GameManager::ChangeWinningMotion()
{
	if (m_PlayerData->ReturnMotion() == MOTION_WIN1)
		m_PlayerData->ChangeMotion(MOTION_WIN2);
	else
		m_PlayerData->ChangeMotion(MOTION_WIN1);
}

void GameManager::CaculatingScore()
{
	if (m_BonusScore > 0)
	{
		m_BonusScore -= 10;
		m_PlayerData->PlusScore(10);
	}

	if (0 == m_BonusScore)
		m_NowState = STATE_WIN_SHUTDOWN;
}

bool GameManager::IsGameOver()
{
	if (0 == m_PlayerData->ReturnLife())
	{
		//���� ���� ȭ��
		m_NowState = STATE_GAMEOVER;
		return true;
	}
	else
		return false;
}

GameManager::~GameManager()
{
	delete m_PlayerData;
	DrawMgr->~DrawManager();
}