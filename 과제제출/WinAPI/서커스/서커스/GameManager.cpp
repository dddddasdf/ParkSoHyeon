#include "GameManager.h"

void GameManager::WholeInit(HWND hWnd)
{
	ResourceMgr->InitImages();
	DrawMgr->Init(hWnd);
	m_PlayerData = new Player;
	m_IsMoving = false;
	m_IsHighest = false;
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
	m_IsHighest를 통해 고도를 조절한다. 
	false일 때 고도를 순차적으로 올리고 최고 고도에 도달하면 m_IsHighest를 true로 교체한 다음 고도를 순차적으로 내린다
	지평선 좌표에 도달하면 m_IsHighest를 false로 돌리고 m_IsJumping 또한 false로 돌린 다음 마지막으로 캐릭터의 모션을 스탠딩으로 교체한다
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
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000)
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
	}
	else
		m_PlayerData->ChangeMotion(MOTION_STAND);

	/*
	지금 보니까 모션이 달리는 중에는 캐릭터 스프라이트 2, 3이 번갈아가면서 나오더라
	일단 구현을 위해서 이렇게 하였다... 모션을 바꾸는 함수인 이 함수가 호출되는 순간 키입력이 지속적으로 이루어지고 있다면 다른 달리는 모션으로
	없다면 스탠딩으로
	*/

	m_IsMoving = false;
}

void GameManager::DrawCharacterOrder(HDC *hdc, HWND hWnd)
{
	DrawMgr->DrawImages(*hdc, m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation());
}