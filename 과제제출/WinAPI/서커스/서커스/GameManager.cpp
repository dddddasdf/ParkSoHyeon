#include "GameManager.h"

void GameManager::WholeInit(HWND hWnd)
{
	ResourceMgr->InitImages();
	DrawMgr->Init(hWnd);
	m_PlayerData = new Player;
	m_IsMoving = false;
	m_IsJumping = false;
	m_IsHighest = false;
	m_MovingDirection = NULL;
	m_IsDeadTrigger = false;
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
		if (HORIZON_CHARACTER <= m_PlayerData->ReturnCharacterYLocation())
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
	if (m_MovingDirection == VK_RIGHT)
	{
		DrawMgr->MoveRings((RING_MOVE_PIXEL + 500) * elapsed, (LITTLERING_MOVE_PIXEL + 500) * elapsed);
	}
	else if (m_MovingDirection == VK_LEFT && m_PlayerData->ReturnCharacterXLocation() > 0)
	{
		DrawMgr->MoveRings((RING_MOVE_PIXEL - 500) * elapsed, (LITTLERING_MOVE_PIXEL - 450) * elapsed);
	}
	else
		DrawMgr->MoveRings(RING_MOVE_PIXEL * elapsed, LITTLERING_MOVE_PIXEL * elapsed);


	/*
	ó������ �� �Լ����� Ű�Է��� �������� ������ �� ��� ���� ���� ����Ű�� �ٲ������ ���� �ӵ��� �޶����� ������ �߻�
	�׷� ��� �����̴� �Լ����� ��� ������ ��� �������� �����̰� �ִٴ� ���� �����Ͽ� �� ������ �̿��Ͽ� ���� �������� ��ü�ϵ��� ��

	�����ϱ� �ߴµ� �� �ڽŵ� ������ �𸣰ڴ� ������ ����
	*/
}

void GameManager::CollisionCheck()
{
	DrawMgr->IsCashCollision(m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterYLocation());

	if (DrawMgr->IsObstacleCollision(m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation()))
	{
		m_PlayerData->ChangeMotion(MOTION_DEAD);
		m_IsDeadTrigger = true;
	}
}

void GameManager::DrawCharacterOrder(HDC *hdc, HWND hWnd)
{
	DrawMgr->DrawImages(*hdc, m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation());
}